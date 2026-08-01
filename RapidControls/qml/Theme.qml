// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

pragma Singleton
import QtQuick
import QtQuick.Controls

QtObject {
    readonly property bool usesDarkAppearance: Qt.application.styleHints.colorScheme === Qt.ColorScheme.Dark

    readonly property int spacingExtraSmall: 4
    readonly property int spacingSmall: 8
    readonly property int spacingMedium: 12
    readonly property int spacingLarge: 16
    readonly property int controlHeight: 32

    readonly property color primaryColor: usesDarkAppearance ? "#479EF5" : "#0F6CBD"
    readonly property color primaryHoverColor: usesDarkAppearance ? "#62ABF5" : "#115EA3"
    readonly property color primaryPressedColor: usesDarkAppearance ? "#2886DE" : "#0C3B5E"
    readonly property color primaryDisabledColor: usesDarkAppearance ? "#3B4A5C" : "#D1D1D1"
    readonly property color primaryTextColor: usesDarkAppearance ? "#0F1720" : "#FFFFFF"
    readonly property color primaryFocusBorderColor: usesDarkAppearance ? "#0F1720" : "#FFFFFF"
    readonly property color disabledTextColor: usesDarkAppearance ? "#8A96A3" : "#9E9E9E"
    readonly property color surfaceColor: usesDarkAppearance ? "#202020" : "#FFFFFF"
    readonly property color surfaceMutedColor: usesDarkAppearance ? "#292929" : "#F5F5F5"
    readonly property color borderColor: usesDarkAppearance ? "#666666" : "#D1D1D1"
    readonly property color textColor: usesDarkAppearance ? "#FFFFFF" : "#1A1A1A"
    readonly property color secondaryTextColor: usesDarkAppearance ? "#C7C7C7" : "#616161"
    readonly property color focusColor: usesDarkAppearance ? "#62ABF5" : "#0067C0"
}
