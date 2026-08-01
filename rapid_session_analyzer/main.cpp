// SPDX-FileCopyrightText: 2026 All contributors
// SPDX-License-Identifier: GPL-2.0-or-later

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    // Ensure import path includes CMake generated QML modules
    engine.addImportPath(QStringLiteral("qml"));

    const QUrl url(QStringLiteral("qrc:/qml/RapidLaptimer/AppShell.qml"));
    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
