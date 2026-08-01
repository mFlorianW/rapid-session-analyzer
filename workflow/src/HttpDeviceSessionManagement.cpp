// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Workflow/HttpDeviceSessionManagement.hpp>

#include <Common/Json.hpp>
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>

namespace RapidSessionAnalyzer::Workflow
{
namespace
{

std::expected<QByteArray, QString> executeGet(QNetworkAccessManager& networkAccessManager,
                                              QUrl const& url,
                                              int requestTimeoutMs)
{
    QNetworkRequest request{url};
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));

    QEventLoop eventLoop;
    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);

    bool didTimeout = false;
    QNetworkReply* reply = networkAccessManager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    QObject::connect(&timeoutTimer, &QTimer::timeout, reply, [&didTimeout, reply] {
        didTimeout = true;
        reply->abort();
    });
    QObject::connect(&timeoutTimer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);

    timeoutTimer.start(requestTimeoutMs);
    eventLoop.exec();

    QByteArray const payload = reply->readAll();
    int const statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QString const errorString = reply->errorString();
    QNetworkReply::NetworkError const networkError = reply->error();
    reply->deleteLater();

    if (didTimeout) {
        return std::unexpected(QStringLiteral("GET '%1' timed out after %2 ms.").arg(url.toString()).arg(requestTimeoutMs));
    }

    if (networkError != QNetworkReply::NoError) {
        return std::unexpected(QStringLiteral("GET '%1' failed: %2").arg(url.toString(), errorString));
    }

    if (statusCode < 200 || statusCode >= 300) {
        return std::unexpected(QStringLiteral("GET '%1' returned HTTP %2: %3")
                                   .arg(url.toString())
                                   .arg(statusCode)
                                   .arg(QString::fromUtf8(payload)));
    }

    return payload;
}

std::expected<QVector<Common::SessionInfo>, QString> parseSessionInfos(QByteArray const& payload)
{
    QJsonParseError parseError;
    QJsonDocument const document = QJsonDocument::fromJson(payload, &parseError);
    if (document.isNull()) {
        return std::unexpected(QStringLiteral("Failed to parse session list JSON: %1").arg(parseError.errorString()));
    }

    if (!document.isArray()) {
        return std::unexpected(QStringLiteral("Expected session list response to be a JSON array."));
    }

    QVector<Common::SessionInfo> sessionInfos;
    QJsonArray const sessionInfoArray = document.array();
    sessionInfos.reserve(sessionInfoArray.size());
    for (QJsonValue const& value : sessionInfoArray) {
        if (!value.isObject()) {
            return std::unexpected(QStringLiteral("Expected each session list entry to be a JSON object."));
        }

        auto sessionInfo = Common::sessionInfoFromJson(QJsonDocument{value.toObject()}.toJson(QJsonDocument::Compact));
        if (!sessionInfo) {
            return std::unexpected(sessionInfo.error());
        }

        sessionInfos.append(*sessionInfo);
    }

    return sessionInfos;
}

QUrl endpointUrl(QUrl baseUrl, QStringView path)
{
    QString normalizedPath = baseUrl.path();
    if (normalizedPath.isEmpty()) {
        normalizedPath = QStringLiteral("/");
    }
    if (!normalizedPath.endsWith(u'/')) {
        normalizedPath.append(u'/');
    }

    QString const relativePath = path.mid(path.startsWith(u'/') ? 1 : 0).toString();
    baseUrl.setPath(normalizedPath + relativePath);
    return baseUrl;
}

} // namespace

HttpDeviceSessionManagement::HttpDeviceSessionManagement(QUrl baseUrl, int requestTimeoutMs)
    : HttpDeviceSessionManagement(std::move(baseUrl), new QNetworkAccessManager, requestTimeoutMs)
{
    mOwnedNetworkAccessManager.reset(mNetworkAccessManager);
}

HttpDeviceSessionManagement::HttpDeviceSessionManagement(QUrl baseUrl,
                                                         QNetworkAccessManager* networkAccessManager,
                                                         int requestTimeoutMs)
    : mBaseUrl(std::move(baseUrl))
    , mNetworkAccessManager(networkAccessManager)
    , mRequestTimeoutMs(requestTimeoutMs)
{
}

std::expected<QVector<Common::SessionInfo>, QString> HttpDeviceSessionManagement::getSessionInfos() const
{
    if (mNetworkAccessManager == nullptr) {
        return std::unexpected(QStringLiteral("No network access manager configured."));
    }

    auto payload = executeGet(*mNetworkAccessManager, endpointUrl(mBaseUrl, u"/v1/sessions"), mRequestTimeoutMs);
    if (!payload) {
        return std::unexpected(payload.error());
    }

    return parseSessionInfos(*payload);
}

std::expected<Common::Session, QString> HttpDeviceSessionManagement::load(QStringView sessionId) const
{
    if (mNetworkAccessManager == nullptr) {
        return std::unexpected(QStringLiteral("No network access manager configured."));
    }

    if (sessionId.isEmpty()) {
        return std::unexpected(QStringLiteral("Session id must not be empty."));
    }

    auto payload = executeGet(
        *mNetworkAccessManager,
        endpointUrl(mBaseUrl, QStringLiteral("/v1/sessions/%1").arg(sessionId)),
        mRequestTimeoutMs);
    if (!payload) {
        return std::unexpected(payload.error());
    }

    return Common::sessionFromJson(*payload);
}

} // namespace RapidSessionAnalyzer::Workflow
