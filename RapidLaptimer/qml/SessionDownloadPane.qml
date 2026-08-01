// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import Rapid.Controls
import RapidLaptimer

Pane {
    id: root

    property alias sessionBrowser: browser
    property string connectButtonText: connectButton.text
    property string addressPlaceholderText: addressField.placeholderText

    implicitWidth: 640
    implicitHeight: contentColumn.implicitHeight + 32
    padding: 16

    background: Rectangle {
        radius: 12
        color: Theme.surfaceColor
        border.width: 1
        border.color: Theme.borderColor
    }

    LaptimerSessionBrowser {
        id: browser
    }

    Column {
        id: contentColumn
        width: parent.width
        spacing: 12

        Label {
            text: "Download Sessions"
            font.bold: true
            font.pointSize: 14
            color: Theme.textColor
        }

        Row {
            width: parent.width
            spacing: 8

            TextField {
                id: addressField

                width: parent.width - connectButton.width - parent.spacing
                placeholderText: "http://rapid-rusty.local"
                text: browser.laptimerAddress
                onTextEdited: browser.laptimerAddress = text
            }

            PrimaryButton {
                id: connectButton

                text: "Connect"
                onClicked: browser.connectToLaptimer()
            }
        }

        ListView {
            id: sessionList

            width: parent.width
            implicitHeight: contentHeight
            height: Math.min(contentHeight, 320)
            clip: true
            spacing: 8
            model: browser.availableSessions

            delegate: Rectangle {
                required property var modelData

                width: sessionList.width
                radius: 8
                color: Theme.surfaceMutedColor
                border.width: 1
                border.color: Theme.borderColor
                implicitHeight: sessionRow.implicitHeight + 16

                Row {
                    id: sessionRow

                    x: 8
                    y: 8
                    width: parent.width - 16
                    spacing: 8

                    Column {
                        width: parent.width - downloadButton.width - sessionRow.spacing
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

                    PrimaryButton {
                        id: downloadButton

                        text: "Download"
                        onClicked: browser.downloadSession(modelData.id)
                    }
                }
            }
        }

        Label {
            width: parent.width
            wrapMode: Text.Wrap
            text: browser.statusMessage
            color: Theme.textColor
            visible: text.length > 0
        }
    }
}
