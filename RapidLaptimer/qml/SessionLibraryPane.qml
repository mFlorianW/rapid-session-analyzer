// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import Rapid.Controls
import RapidLaptimer

Pane {
    id: root
    implicitWidth: 800
    implicitHeight: 600
    padding: 12

    Column {
        anchors.fill: parent
        spacing: 12

        Label { text: qsTr("Session Library"); font.bold: true; font.pointSize: 14 }

        // Placeholder: integrate a proper SessionListModel-backed view later
        Rectangle {
            width: parent.width
            height: 400
            radius: 8
            color: Theme.surfaceMutedColor
            border.width: 1
            border.color: Theme.borderColor

            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8

                Label { text: qsTr("No sessions downloaded yet") }
                Label { text: qsTr("Use 'Download Sessions' to fetch from a laptimer.") }
            }
        }

        Row {
            spacing: 8
            PrimaryButton { text: qsTr("Refresh") }
            PrimaryButton { text: qsTr("Open in Browser") }
        }
    }
}
