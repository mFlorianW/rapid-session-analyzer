// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls

Dialog {
    id: control

    modal: true
    padding: Theme.spacingLarge

    background: Rectangle {
        radius: 8
        color: Theme.surfaceColor
        border.width: 1
        border.color: Theme.borderColor
    }
}
