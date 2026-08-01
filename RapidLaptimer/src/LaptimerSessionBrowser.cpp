// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <RapidLaptimer/LaptimerSessionBrowser.hpp>

#include <Workflow/FilesystemStorage.hpp>
#include <Workflow/HttpLaptimerSessionManagement.hpp>
#include <QDir>
#include <QStandardPaths>
#include <QVariantMap>

namespace RapidSessionAnalyzer::RapidLaptimer
{
namespace
{

std::expected<QUrl, QString> normalizeLaptimerUrl(QStringView address)
{
    QString candidate = address.trimmed().toString();
    if (candidate.isEmpty()) {
        return std::unexpected(QStringLiteral("Laptimer address must not be empty."));
    }

    if (!candidate.contains(QStringLiteral("://"))) {
        candidate.prepend(QStringLiteral("http://"));
    }

    QUrl const url{candidate};
    if (!url.isValid() || url.scheme().isEmpty() || url.host().isEmpty()) {
        return std::unexpected(QStringLiteral("Laptimer address '%1' is not a valid HTTP address.").arg(address));
    }

    if (url.scheme() != QStringLiteral("http") && url.scheme() != QStringLiteral("https")) {
        return std::unexpected(QStringLiteral("Laptimer address '%1' must use http or https.").arg(address));
    }

    return url;
}

QString defaultSessionLibraryPath()
{
    QString const appDataDirectory = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (appDataDirectory.isEmpty()) {
        return {};
    }

    return QDir{appDataDirectory}.filePath(QStringLiteral("sessions"));
}

QVariantList toVariantList(QVector<Common::SessionInfo> const& sessionInfos)
{
    QVariantList sessions;
    sessions.reserve(sessionInfos.size());
    for (Common::SessionInfo const& sessionInfo : sessionInfos) {
        sessions.append(QVariantMap{
            {QStringLiteral("id"), sessionInfo.id},
            {QStringLiteral("date"), sessionInfo.date.toString(Qt::ISODateWithMs)},
            {QStringLiteral("trackName"), sessionInfo.trackName},
            {QStringLiteral("laps"), sessionInfo.laps},
        });
    }

    return sessions;
}

void updateStatusMessage(QString& currentValue, QString nextValue, LaptimerSessionBrowser& browser)
{
    if (currentValue == nextValue) {
        return;
    }

    currentValue = std::move(nextValue);
    Q_EMIT browser.statusMessageChanged();
}

void updateAvailableSessions(QVariantList& currentValue, QVariantList nextValue, LaptimerSessionBrowser& browser)
{
    if (currentValue == nextValue) {
        return;
    }

    currentValue = std::move(nextValue);
    Q_EMIT browser.availableSessionsChanged();
}

void updateDownloadedSessions(QVariantList& currentValue, QVariantList nextValue, LaptimerSessionBrowser& browser)
{
    if (currentValue == nextValue) {
        return;
    }

    currentValue = std::move(nextValue);
    Q_EMIT browser.downloadedSessionsChanged();
}

} // namespace

LaptimerSessionBrowser::LaptimerSessionBrowser(QObject* parent)
    : QObject(parent)
    , mSessionLibraryPath(defaultSessionLibraryPath())
{
}

QString LaptimerSessionBrowser::laptimerAddress() const
{
    return mLaptimerAddress;
}

void LaptimerSessionBrowser::setLaptimerAddress(QString laptimerAddress)
{
    if (mLaptimerAddress == laptimerAddress) {
        return;
    }

    mLaptimerAddress = std::move(laptimerAddress);
    Q_EMIT laptimerAddressChanged();
}

QString LaptimerSessionBrowser::sessionLibraryPath() const
{
    return mSessionLibraryPath;
}

void LaptimerSessionBrowser::setSessionLibraryPath(QString sessionLibraryPath)
{
    if (mSessionLibraryPath == sessionLibraryPath) {
        return;
    }

    mSessionLibraryPath = std::move(sessionLibraryPath);
    Q_EMIT sessionLibraryPathChanged();
    refreshSessionLibrary();
}

QVariantList LaptimerSessionBrowser::availableSessions() const
{
    return mAvailableSessions;
}

QVariantList LaptimerSessionBrowser::downloadedSessions() const
{
    return mDownloadedSessions;
}

QString LaptimerSessionBrowser::statusMessage() const
{
    return mStatusMessage;
}

void LaptimerSessionBrowser::connectToLaptimer()
{
    auto normalizedUrl = normalizeLaptimerUrl(mLaptimerAddress);
    if (!normalizedUrl) {
        updateAvailableSessions(mAvailableSessions, {}, *this);
        updateStatusMessage(mStatusMessage, normalizedUrl.error(), *this);
        return;
    }

    Workflow::HttpLaptimerSessionManagement sessionManagement{*normalizedUrl};
    auto sessionInfos = sessionManagement.getSessionInfos();
    if (!sessionInfos) {
        updateAvailableSessions(mAvailableSessions, {}, *this);
        updateStatusMessage(mStatusMessage, sessionInfos.error(), *this);
        return;
    }

    updateAvailableSessions(mAvailableSessions, toVariantList(*sessionInfos), *this);
    updateStatusMessage(
        mStatusMessage,
        QStringLiteral("Loaded %1 session(s) from %2.").arg(sessionInfos->size()).arg(normalizedUrl->toString()),
        *this);
}

std::expected<void, QString> LaptimerSessionBrowser::reloadSessionLibrary()
{
    if (mSessionLibraryPath.trimmed().isEmpty()) {
        return std::unexpected(QStringLiteral("Session Library path must not be empty."));
    }

    Workflow::FilesystemStorage storage{QDir{mSessionLibraryPath}};
    auto sessionInfos = storage.getSessionInfos();
    if (!sessionInfos) {
        return std::unexpected(sessionInfos.error());
    }

    updateDownloadedSessions(mDownloadedSessions, toVariantList(*sessionInfos), *this);
    return {};
}

void LaptimerSessionBrowser::refreshSessionLibrary()
{
    auto result = reloadSessionLibrary();
    if (!result) {
        updateStatusMessage(mStatusMessage, result.error(), *this);
    }
}

void LaptimerSessionBrowser::downloadSession(QString const& sessionId)
{
    auto normalizedUrl = normalizeLaptimerUrl(mLaptimerAddress);
    if (!normalizedUrl) {
        updateStatusMessage(mStatusMessage, normalizedUrl.error(), *this);
        return;
    }

    if (mSessionLibraryPath.trimmed().isEmpty()) {
        updateStatusMessage(mStatusMessage, QStringLiteral("Session Library path must not be empty."), *this);
        return;
    }

    Workflow::HttpLaptimerSessionManagement sessionManagement{*normalizedUrl};
    auto session = sessionManagement.load(sessionId);
    if (!session) {
        updateStatusMessage(mStatusMessage, session.error(), *this);
        return;
    }

    Workflow::FilesystemStorage storage{QDir{mSessionLibraryPath}};
    auto storeResult = storage.store(sessionId, *session);
    if (!storeResult) {
        updateStatusMessage(mStatusMessage, storeResult.error(), *this);
        return;
    }

    auto refreshedSessionLibrary = reloadSessionLibrary();
    if (!refreshedSessionLibrary) {
        updateStatusMessage(mStatusMessage, refreshedSessionLibrary.error(), *this);
        return;
    }

    updateStatusMessage(
        mStatusMessage,
        QStringLiteral("Downloaded session '%1' into the Session Library.").arg(sessionId),
        *this);
}

} // namespace RapidSessionAnalyzer::RapidLaptimer
