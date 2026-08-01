// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls

TextField {
    id: control

    implicitHeight: Theme.controlHeight
    leftPadding: Theme.spacingSmall
    rightPadding: Theme.spacingSmall
    topPadding: Theme.spacingExtraSmall
    bottomPadding: Theme.spacingExtraSmall
    color: control.enabled ? Theme.textColor : Theme.disabledTextColor
    placeholderTextColor: Theme.secondaryTextColor
    selectByMouse: true
    hoverEnabled: true

    background: Rectangle {
        radius: 4
        color: Theme.surfaceColor
        border.width: control.activeFocus ? 2 : 1
        border.color: control.activeFocus ? Theme.focusColor : control.hovered ? Theme.secondaryTextColor : Theme.borderColor
    }
}
