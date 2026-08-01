// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls

Button {
    id: control

    implicitHeight: Theme.controlHeight
    leftPadding: Theme.spacingMedium
    rightPadding: Theme.spacingMedium
    topPadding: Theme.spacingExtraSmall
    bottomPadding: Theme.spacingExtraSmall
    hoverEnabled: true

    contentItem: Text {
        text: control.text
        color: control.enabled ? Theme.primaryTextColor : Theme.disabledTextColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font: control.font
    }

    background: Rectangle {
        radius: 4
        color: !control.enabled ? Theme.primaryDisabledColor : control.down ? Theme.primaryPressedColor : control.hovered ? Theme.primaryHoverColor : Theme.primaryColor
        border.width: control.visualFocus ? 2 : 0
        border.color: Theme.primaryFocusBorderColor
    }
}
