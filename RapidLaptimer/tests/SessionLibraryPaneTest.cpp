// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <RapidLaptimer/LaptimerSessionBrowser.hpp>
#include <TestHelper/SessionSamples.hpp>
#include <Workflow/FilesystemStorage.hpp>
#include <QCoreApplication>
#include <QDir>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>
#include <QTemporaryDir>
#include <QTest>
#include <memory>

using namespace RapidSessionAnalyzer;

class SessionLibraryPaneTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void rendersSessionsStoredInTheSessionLibrary()
    {
        QTemporaryDir temporaryDir;
        QVERIFY2(temporaryDir.isValid(), "Expected a writable temporary directory.");

        Workflow::FilesystemStorage storage{QDir{temporaryDir.path()}};
        QVERIFY(storage.store(TestHelper::oscherslebenSessionId(), TestHelper::oscherslebenSession()).has_value());

        RapidLaptimer::LaptimerSessionBrowser sessionBrowser;
        sessionBrowser.setSessionLibraryPath(temporaryDir.path());

        QQmlEngine engine;
        engine.addImportPath(QDir{QCoreApplication::applicationDirPath()}.absoluteFilePath(QStringLiteral("../qml")));
        engine.rootContext()->setContextProperty(QStringLiteral("injectedSessionBrowser"), &sessionBrowser);
        QQmlComponent component{&engine};
        component.setData(
            R"(
                import QtQuick
                import RapidLaptimer

                SessionLibraryPane {
                    sessionBrowser: injectedSessionBrowser
                }
            )",
            QUrl{});

        QVERIFY2(component.isReady(), qPrintable(component.errorString()));
        std::unique_ptr<QObject> instance{component.create()};
        QVERIFY(instance != nullptr);
        QCOMPARE(instance->property("sessionCount").toInt(), 1);
    }
};

QTEST_MAIN(SessionLibraryPaneTest)
#include "SessionLibraryPaneTest.moc"
