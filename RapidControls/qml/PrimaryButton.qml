// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls

Button {
    id: control

    padding: 12
    font.pointSize: 11
    font.bold: true

    contentItem: Text {
        text: control.text
        color: Theme.primaryTextColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font: control.font
    }

    background: Rectangle {
        radius: 8
        color: control.down ? Theme.primaryPressedColor : Theme.primaryColor
        border.width: control.visualFocus ? 2 : 0
        border.color: Theme.borderColor
    }
}
