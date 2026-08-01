// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Common/Json.hpp>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTemporaryDir>
#include <QTest>
#include <RapidLaptimer/LaptimerSessionBrowser.hpp>
#include <TestHelper/SessionSamples.hpp>

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
        QObject::connect(socket, &QTcpSocket::readyRead, this, [socket] {
            QByteArray const request = socket->readAll();
            QByteArray const requestLine = request.split('\n').value(0).trimmed();
            QByteArray const path = requestLine.split(' ').value(1);

            if (path == "/v1/sessions") {
                QJsonArray sessions;
                sessions.append(QJsonDocument::fromJson(Common::toJson(TestHelper::oscherslebenSessionInfo())).object());
                QJsonObject const payload{
                    {QStringLiteral("total"), sessions.size()},
                    {QStringLiteral("sessions"), sessions},
                };
                writeResponse(socket, QJsonDocument{payload}.toJson(QJsonDocument::Compact));
                return;
            }

            if (path == QByteArrayLiteral("/v1/sessions/") + TestHelper::oscherslebenSessionId().toUtf8()) {
                writeResponse(socket, Common::toJson(TestHelper::oscherslebenSession()));
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
};

} // namespace

class LaptimerSessionBrowserTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void connectsListsSessionsAndDownloadsIntoSessionLibrary()
    {
        FakeLaptimerServer server;
        QVERIFY2(server.listen(), "Expected fake laptimer server to start.");

        QTemporaryDir temporaryDir;
        QVERIFY2(temporaryDir.isValid(), "Expected a writable temporary directory.");

        RapidLaptimer::LaptimerSessionBrowser browser;
        browser.setLaptimerAddress(server.baseUrl().toString());
        browser.setSessionLibraryPath(temporaryDir.path());

        browser.connectToLaptimer();

        QVariantList const availableSessions = browser.availableSessions();
        QCOMPARE(availableSessions.size(), 1);
        QCOMPARE(availableSessions.front().toMap().value(QStringLiteral("id")).toString(),
                 TestHelper::oscherslebenSessionId());

        browser.downloadSession(TestHelper::oscherslebenSessionId());

        QFile file{temporaryDir.filePath(QStringLiteral("%1.json").arg(TestHelper::oscherslebenSessionId()))};
        QVERIFY(file.open(QIODevice::ReadOnly));
        QCOMPARE(file.readAll(), Common::toJson(TestHelper::oscherslebenSession()));

        QVariantList const downloadedSessions = browser.downloadedSessions();
        QCOMPARE(downloadedSessions.size(), 1);
        QCOMPARE(downloadedSessions.front().toMap().value(QStringLiteral("id")).toString(),
                 TestHelper::oscherslebenSessionId());
    }

    void rejectsNonHttpAddresses()
    {
        RapidLaptimer::LaptimerSessionBrowser browser;
        browser.setLaptimerAddress(QStringLiteral("ftp://rapid-rusty.local"));

        browser.connectToLaptimer();

        QCOMPARE(browser.statusMessage(), QStringLiteral("Laptimer address 'ftp://rapid-rusty.local' must use http or https."));
        QVERIFY(browser.availableSessions().isEmpty());
    }
};

QTEST_MAIN(LaptimerSessionBrowserTest)
#include "LaptimerSessionBrowserTest.moc"
