// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import Rapid.Controls
import RapidLaptimer

Pane {
    id: root
    required property LaptimerSessionBrowser sessionBrowser
    property int sessionCount: sessionList.count
    implicitWidth: 800
    implicitHeight: 600
    padding: 12

    Column {
        anchors.fill: parent
        spacing: 12

        Label { text: qsTr("Session Library"); font.bold: true; font.pointSize: 14 }

        ListView {
            id: sessionList

            width: parent.width
            implicitHeight: contentHeight
            height: Math.min(contentHeight, 400)
            clip: true
            spacing: 8
            model: root.sessionBrowser.downloadedSessions

            delegate: Rectangle {
                required property var modelData

                width: sessionList.width
                radius: 8
                color: Theme.surfaceMutedColor
                border.width: 1
                border.color: Theme.borderColor
                implicitHeight: sessionDetails.implicitHeight + 16

                Column {
                    id: sessionDetails

                    x: 8
                    y: 8
                    width: parent.width - 16
                    spacing: 2

                    Label {
                        text: modelData.trackName
                        font.bold: true
                        color: Theme.textColor
                    }

                    Label {
                        text: modelData.date + " - " + modelData.laps + " lap(s)"
                        color: Theme.textColor
                    }

                    Label {
                        text: modelData.id
                        color: Theme.textColor
                        opacity: 0.7
                    }
                }
            }
        }

        Label {
            visible: root.sessionCount === 0
            text: qsTr("No sessions downloaded yet")
        }

        Label {
            visible: root.sessionCount === 0
            text: qsTr("Use 'Download Sessions' to fetch from a laptimer.")
        }

        Row {
            spacing: 8
            PrimaryButton {
                text: qsTr("Refresh")
                onClicked: root.sessionBrowser.refreshSessionLibrary()
            }
            PrimaryButton { text: qsTr("Open in Browser") }
        }
    }

    Component.onCompleted: root.sessionBrowser.refreshSessionLibrary()
}
