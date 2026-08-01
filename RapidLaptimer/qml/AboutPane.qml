// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import Rapid.Controls

Pane {
    implicitWidth: 640
    implicitHeight: 360
    padding: Theme.spacingLarge

    background: Rectangle {
        color: Theme.surfaceColor
    }

    Column {
        width: parent.width
        spacing: Theme.spacingMedium

        Row {
            spacing: Theme.spacingSmall

            FluentIcon {
                iconName: "info"
            }

            Label {
                text: qsTr("About Rapid Session Analyzer")
                font.bold: true
                font.pointSize: 14
                color: Theme.textColor
            }
        }

        Label {
            width: parent.width
            text: qsTr("Browse and analyze driving sessions downloaded from your Laptimer.")
            wrapMode: Text.Wrap
            color: Theme.textColor
        }
    }
}
