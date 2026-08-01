// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls

Pane {
    id: control

    property string message

    implicitHeight: statusLabel.implicitHeight + topPadding + bottomPadding
    padding: Theme.spacingSmall
    visible: message.length > 0

    background: Rectangle {
        radius: 4
        color: Theme.surfaceMutedColor
        border.width: 1
        border.color: Theme.borderColor
    }

    contentItem: Label {
        id: statusLabel

        width: parent.width
        text: control.message
        wrapMode: Text.Wrap
        color: Theme.textColor
    }
}
