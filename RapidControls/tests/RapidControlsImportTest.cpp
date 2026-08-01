// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <QColor>
#include <QCoreApplication>
#include <QDir>
#include <QGuiApplication>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>
#include <QStyleHints>
#include <QTest>
#include <QUrl>
#include <algorithm>
#include <cmath>
#include <memory>

namespace
{

qreal linearizedChannel(qreal channel)
{
    return channel <= 0.04045 ? channel / 12.92 : std::pow((channel + 0.055) / 1.055, 2.4);
}

qreal relativeLuminance(QColor const& color)
{
    return 0.2126 * linearizedChannel(color.redF()) + 0.7152 * linearizedChannel(color.greenF()) +
           0.0722 * linearizedChannel(color.blueF());
}

qreal contrastRatio(QColor const& first, QColor const& second)
{
    auto const lighter = std::max(relativeLuminance(first), relativeLuminance(second));
    auto const darker = std::min(relativeLuminance(first), relativeLuminance(second));
    return (lighter + 0.05) / (darker + 0.05);
}

} // namespace

class RapidControlsImportTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void importsRapidControlsAndCreatesStyledButton()
    {
        QQmlEngine engine;
        engine.addImportPath(QDir{QCoreApplication::applicationDirPath()}.absoluteFilePath(QStringLiteral("../qml")));
        QQmlComponent component{
            &engine,
            QUrl::fromLocalFile(QStringLiteral("%1/tests/RapidControlsImportTest.qml").arg(QT_TESTCASE_SOURCEDIR)),
        };

        std::unique_ptr<QObject> instance{component.create()};

        QVERIFY2(component.isReady(), qPrintable(component.errorString()));
        QVERIFY(instance != nullptr);

        auto* item = qobject_cast<QQuickItem*>(instance.get());
        QVERIFY(item != nullptr);
        QCOMPARE(instance->property("buttonText").toString(), QStringLiteral("Analyze"));
        QCOMPARE(instance->property("usesDarkAppearance").toBool(),
                 QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark);
        QCOMPARE(instance->property("primaryButtonHeight").toDouble(), 32.0);
        QCOMPARE(instance->property("textFieldHeight").toDouble(), 32.0);
        QCOMPARE(instance->property("libraryIconSize").toInt(), 24);
        QVERIFY(contrastRatio(instance->property("primaryColor").value<QColor>(),
                              instance->property("primaryFocusBorderColor").value<QColor>()) >= 3.0);
    }
};

QTEST_MAIN(RapidControlsImportTest)
#include "RapidControlsImportTest.moc"
