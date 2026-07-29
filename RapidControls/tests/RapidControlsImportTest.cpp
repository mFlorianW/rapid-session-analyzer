// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <QCoreApplication>
#include <QDir>
#include <QQuickItem>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QTest>
#include <memory>

class RapidControlsImportTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void importsRapidControlsAndCreatesStyledButton()
    {
        QQmlEngine engine;
        engine.addImportPath(QDir{QCoreApplication::applicationDirPath()}.absoluteFilePath(QStringLiteral("../qml")));
        QQmlComponent component{&engine};
        component.setData(R"qml(
import QtQuick
import Rapid.Controls

PrimaryButton {
    text: "Analyze"
}
)qml",
            QUrl{QStringLiteral("file:///RapidControlsImportTest.qml")});

        std::unique_ptr<QObject> instance{component.create()};

        QVERIFY2(component.isReady(), qPrintable(component.errorString()));
        QVERIFY(instance != nullptr);

        auto* item = qobject_cast<QQuickItem*>(instance.get());
        QVERIFY(item != nullptr);
        QCOMPARE(instance->property("text").toString(), QStringLiteral("Analyze"));
        QVERIFY(item->implicitWidth() > 0.0);
        QVERIFY(item->implicitHeight() > 0.0);
    }
};

QTEST_MAIN(RapidControlsImportTest)
#include "RapidControlsImportTest.moc"
