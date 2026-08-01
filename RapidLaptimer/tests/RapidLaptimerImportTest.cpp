// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <QCoreApplication>
#include <QDir>
#include <QQuickItem>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QUrl>
#include <QTest>
#include <algorithm>
#include <memory>

class RapidLaptimerImportTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void importsRapidLaptimerAndCreatesSessionDownloadPane()
    {
        QQmlEngine engine;
        engine.addImportPath(QDir{QCoreApplication::applicationDirPath()}.absoluteFilePath(QStringLiteral("../qml")));
        QQmlComponent component{
            &engine,
            QUrl::fromLocalFile(QStringLiteral("%1/tests/RapidLaptimerImportTest.qml").arg(QT_TESTCASE_SOURCEDIR)),
        };

        std::unique_ptr<QObject> instance{component.create()};

        QVERIFY2(component.isReady(), qPrintable(component.errorString()));
        QVERIFY(instance != nullptr);

        auto* item = qobject_cast<QQuickItem*>(instance.get());
        QVERIFY(item != nullptr);
        QCOMPARE(instance->property("connectButtonText").toString(), QStringLiteral("Connect"));
        QCOMPARE(instance->property("addressPlaceholderText").toString(), QStringLiteral("http://rapid-rusty.local"));
        QCOMPARE(instance->property("addressInputAccessibleName").toString(), QStringLiteral("Laptimer address"));
        QCOMPARE(instance->property("connectCommandAccessibleName").toString(), QStringLiteral("Connect to Laptimer"));
        QCOMPARE(instance->property("sessionListAccessibleName").toString(), QStringLiteral("Available Sessions"));
        QCOMPARE(instance->property("statusFeedbackAccessibleName").toString(), QStringLiteral("Laptimer status"));
        QVERIFY(item->implicitWidth() > 0.0);
        QVERIFY(item->implicitHeight() > 0.0);
    }

    void createsAppShellWithSharedSessionBrowser()
    {
        QQmlEngine engine;
        engine.addImportPath(QDir{QCoreApplication::applicationDirPath()}.absoluteFilePath(QStringLiteral("../qml")));
        QQmlComponent component{
            &engine,
            QUrl{QStringLiteral("qrc:/qt/qml/RapidLaptimer/qml/AppShell.qml")},
        };

        std::unique_ptr<QObject> instance{component.create()};

        QVERIFY2(component.isReady(), qPrintable(component.errorString()));
        QVERIFY(instance != nullptr);

        auto const descendants = instance->findChildren<QObject*>();
        auto const sessionLibraryPane = std::find_if(descendants.cbegin(), descendants.cend(), [](QObject* object) {
            return object->metaObject()->indexOfProperty("sessionCount") >= 0;
        });
        QVERIFY(sessionLibraryPane != descendants.cend());
        QVERIFY((*sessionLibraryPane)->property("sessionBrowser").value<QObject*>() != nullptr);
    }

    void replacesTheActiveTopLevelPage()
    {
        QQmlEngine engine;
        engine.addImportPath(QDir{QCoreApplication::applicationDirPath()}.absoluteFilePath(QStringLiteral("../qml")));
        QQmlComponent component{
            &engine,
            QUrl{QStringLiteral("qrc:/qt/qml/RapidLaptimer/qml/AppShell.qml")},
        };

        std::unique_ptr<QObject> instance{component.create()};

        QVERIFY2(component.isReady(), qPrintable(component.errorString()));
        QVERIFY(instance != nullptr);
        QCOMPARE(instance->property("currentDestination").toString(), QStringLiteral("library"));
        QCOMPARE(instance->property("currentPageTitle").toString(), QStringLiteral("Session Library"));

        QVERIFY(QMetaObject::invokeMethod(
            instance.get(), "navigateTo", Q_ARG(QVariant, QVariant{QStringLiteral("download")})));
        QCOMPARE(instance->property("currentDestination").toString(), QStringLiteral("download"));
        QCOMPARE(instance->property("currentPageTitle").toString(), QStringLiteral("Download Sessions"));

        QVERIFY(QMetaObject::invokeMethod(
            instance.get(), "navigateTo", Q_ARG(QVariant, QVariant{QStringLiteral("about")})));
        QCOMPARE(instance->property("currentDestination").toString(), QStringLiteral("about"));
        QCOMPARE(instance->property("currentPageTitle").toString(), QStringLiteral("About"));

        QVERIFY(QMetaObject::invokeMethod(
            instance.get(), "navigateTo", Q_ARG(QVariant, QVariant{QStringLiteral("library")})));
        QCOMPARE(instance->property("currentDestination").toString(), QStringLiteral("library"));

        instance->setProperty("width", 600);
        QCoreApplication::processEvents();
        QCOMPARE(instance->property("navigationMode").toString(), QStringLiteral("compact"));
    }

    void loadsAboutPane()
    {
        QQmlEngine engine;
        engine.addImportPath(QDir{QCoreApplication::applicationDirPath()}.absoluteFilePath(QStringLiteral("../qml")));
        QQmlComponent component{
            &engine,
            QUrl{QStringLiteral("qrc:/qt/qml/RapidLaptimer/qml/AboutPane.qml")},
        };

        std::unique_ptr<QObject> instance{component.create()};

        QVERIFY2(component.isReady(), qPrintable(component.errorString()));
        QVERIFY(instance != nullptr);
    }
};

QTEST_MAIN(RapidLaptimerImportTest)
#include "RapidLaptimerImportTest.moc"
