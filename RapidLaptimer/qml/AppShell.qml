// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import Rapid.Controls
import RapidLaptimer

ApplicationWindow {
    id: app
    visible: true
    width: 1024
    height: 768
    title: qsTr("Rapid Session Analyzer")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            Action { text: qsTr("Quit"); onTriggered: Qt.quit() }
        }
    }

    Drawer {
        id: navDrawer
        width: 240
        height: parent.height

        Column {
            anchors.fill: parent
            spacing: 8
            padding: 12

            Label { text: qsTr("Navigation"); font.bold: true }

            Button { text: qsTr("Session Library"); onClicked: stackView.push("SessionLibraryPane.qml") }
            Button { text: qsTr("Download Sessions"); onClicked: stackView.push("SessionDownloadPane.qml") }
            Button { text: qsTr("About"); onClicked: stackView.push("AboutPane.qml") }
        }
    }

    header: ToolBar {
        Row {
            spacing: 8
            ToolButton { icon.name: "menu"; onClicked: navDrawer.open() }
            Label { text: app.title; font.bold: true }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: "SessionLibraryPane.qml"
    }
}
