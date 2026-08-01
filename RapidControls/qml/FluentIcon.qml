// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick

Item {
    id: root

    required property string iconName

    implicitWidth: 24
    implicitHeight: 24

    function sourceFor(name) {
        const suffix = Theme.usesDarkAppearance ? "-dark.svg" : ".svg";
        const source = {
            "download": "icons/download",
            "info": "icons/info",
            "library": "icons/library"
        }[name];

        return source ? Qt.resolvedUrl(source + suffix) : "";
    }

    Image {
        anchors.fill: parent
        source: root.sourceFor(root.iconName)
        fillMode: Image.PreserveAspectFit
        smooth: true
    }
}
