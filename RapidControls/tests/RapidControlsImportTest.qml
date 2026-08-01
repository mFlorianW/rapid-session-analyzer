// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import Rapid.Controls

Item {
    property string buttonText: primaryButton.text
    property bool usesDarkAppearance: Theme.usesDarkAppearance
    property real primaryButtonHeight: primaryButton.implicitHeight
    property real textFieldHeight: addressField.implicitHeight
    property int libraryIconSize: libraryIcon.implicitWidth
    property color primaryColor: Theme.primaryColor
    property color primaryFocusBorderColor: Theme.primaryFocusBorderColor

    PrimaryButton {
        id: primaryButton

        text: "Analyze"
    }

    FluentTextField {
        id: addressField

        placeholderText: "http://rapid-rusty.local"
    }

    FluentIcon {
        id: libraryIcon

        iconName: "library"
    }
}
