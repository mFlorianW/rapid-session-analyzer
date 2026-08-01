// SPDX-FileCopyrightText: 2026 All contributors
// SPDX-License-Identifier: GPL-2.0-or-later

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QDir>

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Prefer the build/generated qml import path next to the build dir.
    // When the binary is in <build>/bin, the generated qml modules are in <build>/qml.
    const QString exeDir = QCoreApplication::applicationDirPath();
    QDir d(exeDir);
    d.cdUp(); // move from <build>/bin -> <build>
    const QString generatedQmlPath = d.absoluteFilePath("qml");
    engine.addImportPath(generatedQmlPath);

    // Also add the default local qml folder (for running from source tree where CMake copies qml)
    engine.addImportPath(QStringLiteral("qml"));

    // The qml module is exposed in the resource under /qt/qml/<Module>/qml/<File.qml>
    const QUrl url(QStringLiteral("qrc:/qt/qml/RapidLaptimer/qml/AppShell.qml"));
    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
