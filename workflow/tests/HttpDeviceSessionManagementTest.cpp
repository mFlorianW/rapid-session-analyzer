// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Common/Json.hpp>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTest>
#include <TestHelper/SessionSamples.hpp>
#include <Workflow/HttpDeviceSessionManagement.hpp>

using namespace RapidSessionAnalyzer;

namespace
{

class FakeLaptimerServer : public QObject
{
    Q_OBJECT

public:
    explicit FakeLaptimerServer(QObject* parent = nullptr)
        : QObject(parent)
    {
        QObject::connect(&mServer, &QTcpServer::newConnection, this, &FakeLaptimerServer::handleConnection);
    }

    void setSessionInfoResponses(QVector<Common::SessionInfo> sessionInfos)
    {
        mSessionInfos = std::move(sessionInfos);
    }

    void setSessionResponse(Common::Session session)
    {
        mSession = std::move(session);
    }

    bool listen()
    {
        return mServer.listen(QHostAddress::LocalHost);
    }

    [[nodiscard]] QUrl baseUrl() const
    {
        return QUrl{QStringLiteral("http://127.0.0.1:%1").arg(mServer.serverPort())};
    }

private:
    void handleConnection()
    {
        auto* socket = mServer.nextPendingConnection();
        QObject::connect(socket, &QTcpSocket::readyRead, this, [this, socket] {
            QByteArray const request = socket->readAll();
            QByteArray const requestLine = request.split('\n').value(0).trimmed();
            QByteArray const path = requestLine.split(' ').value(1);

            if (path == "/v1/sessions") {
                QJsonArray payload;
                for (Common::SessionInfo const& sessionInfo : mSessionInfos) {
                    payload.append(QJsonDocument::fromJson(Common::toJson(sessionInfo)).object());
                }
                writeResponse(socket, QJsonDocument{payload}.toJson(QJsonDocument::Compact));
                return;
            }

            if (path == QByteArrayLiteral("/v1/sessions/") + TestHelper::oscherslebenSessionInfo().id.toUtf8()) {
                writeResponse(socket, Common::toJson(mSession));
                return;
            }

            writeResponse(socket, QByteArrayLiteral("{\"error\":\"not found\"}"), "404 Not Found");
        });
        QObject::connect(socket, &QTcpSocket::disconnected, socket, &QObject::deleteLater);
    }

    static void writeResponse(QTcpSocket* socket, QByteArray const& body, QByteArray const& status = "200 OK")
    {
        QByteArray const response = QByteArrayLiteral("HTTP/1.1 ") + status + QByteArrayLiteral("\r\n")
                                    + QByteArrayLiteral("Content-Type: application/json\r\n")
                                    + QByteArrayLiteral("Content-Length: ") + QByteArray::number(body.size())
                                    + QByteArrayLiteral("\r\nConnection: close\r\n\r\n") + body;
        socket->write(response);
        socket->disconnectFromHost();
    }

    QTcpServer mServer;
    QVector<Common::SessionInfo> mSessionInfos;
    Common::Session mSession;
};

} // namespace

class HttpDeviceSessionManagementTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void listsSessionInfosFromLaptimerRestApi()
    {
        FakeLaptimerServer server;
        QVERIFY2(server.listen(), "Expected fake laptimer server to start.");
        server.setSessionInfoResponses({TestHelper::oscherslebenSessionInfo()});

        Workflow::HttpDeviceSessionManagement sessionManagement{server.baseUrl()};

        auto sessionInfos = sessionManagement.getSessionInfos();

        QVERIFY(sessionInfos.has_value());
        QCOMPARE(*sessionInfos, QVector<Common::SessionInfo>{TestHelper::oscherslebenSessionInfo()});
    }

    void fetchesFullSessionFromLaptimerRestApi()
    {
        FakeLaptimerServer server;
        QVERIFY2(server.listen(), "Expected fake laptimer server to start.");
        server.setSessionResponse(TestHelper::oscherslebenSession());

        Workflow::HttpDeviceSessionManagement sessionManagement{server.baseUrl()};

        auto session = sessionManagement.load(TestHelper::oscherslebenSessionInfo().id);

        QVERIFY(session.has_value());
        QCOMPARE(*session, TestHelper::oscherslebenSession());
    }
};

QTEST_MAIN(HttpDeviceSessionManagementTest)
#include "HttpDeviceSessionManagementTest.moc"
