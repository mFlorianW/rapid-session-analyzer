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
    property string connectButtonText: connectButton.text
    property string addressPlaceholderText: addressField.placeholderText
    property string addressInputAccessibleName: addressField.Accessible.name
    property string connectCommandAccessibleName: connectButton.Accessible.name
    property string sessionListAccessibleName: sessionList.Accessible.name
    property string statusFeedbackAccessibleName: statusFeedback.Accessible.name

    implicitWidth: 640
    implicitHeight: contentColumn.implicitHeight + Theme.spacingLarge * 2
    padding: Theme.spacingLarge

    background: Rectangle {
        radius: 4
        color: Theme.surfaceColor
        border.width: 1
        border.color: Theme.borderColor
    }

    Column {
        id: contentColumn
        width: parent.width
        spacing: Theme.spacingMedium

        Label {
            text: qsTr("Download Sessions")
            font.bold: true
            font.pointSize: 14
            color: Theme.textColor
        }

        Row {
            width: parent.width
            spacing: Theme.spacingSmall

            FluentTextField {
                id: addressField

                width: parent.width - connectButton.width - parent.spacing
                placeholderText: qsTr("http://rapid-rusty.local")
                text: root.sessionBrowser.laptimerAddress
                onTextEdited: root.sessionBrowser.laptimerAddress = text
                Accessible.name: qsTr("Laptimer address")
            }

            PrimaryButton {
                id: connectButton

                text: qsTr("Connect")
                onClicked: root.sessionBrowser.connectToLaptimer()
                Accessible.name: qsTr("Connect to Laptimer")
            }
        }

        ListView {
            id: sessionList

            width: parent.width
            implicitHeight: contentHeight
            height: Math.min(contentHeight, 320)
            clip: true
            spacing: Theme.spacingSmall
            model: root.sessionBrowser.availableSessions
            Accessible.name: qsTr("Available Sessions")

            delegate: FluentListItem {
                required property var modelData

                width: sessionList.width
                implicitHeight: sessionRow.implicitHeight + Theme.spacingMedium

                Row {
                    id: sessionRow

                    width: parent.width
                    spacing: Theme.spacingSmall

                    Column {
                        width: parent.width - downloadButton.width - sessionRow.spacing
                        spacing: Theme.spacingExtraSmall

                        Label {
                            text: modelData.trackName
                            font.bold: true
                            color: Theme.textColor
                        }

                        Label {
                            text: qsTr("%1 - %2 lap(s)").arg(modelData.date).arg(modelData.laps)
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

                        text: qsTr("Download")
                        onClicked: root.sessionBrowser.downloadSession(modelData.id)
                        Accessible.name: qsTr("Download Session %1").arg(modelData.id)
                    }
                }
            }
        }

        FluentStatusMessage {
            id: statusFeedback

            width: parent.width
            message: root.sessionBrowser.statusMessage
            Accessible.name: qsTr("Laptimer status")
        }
    }
}
