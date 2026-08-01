// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Pane {
    id: control

    default property alias content: contentLayout.data

    padding: Theme.spacingSmall

    background: Rectangle {
        radius: 4
        color: Theme.surfaceMutedColor
        border.width: 1
        border.color: Theme.borderColor
    }

    contentItem: ColumnLayout {
        id: contentLayout

        spacing: Theme.spacingSmall
    }
}
