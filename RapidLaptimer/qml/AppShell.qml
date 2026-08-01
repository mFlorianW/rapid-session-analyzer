// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Rapid.Controls
import RapidLaptimer

ApplicationWindow {
    id: app
    visible: true
    width: 1024
    height: 768
    title: qsTr("Rapid Session Analyzer")
    property bool compactNavigation: width < 720
    property string currentDestination: ["library", "download", "about"][pageStack.currentIndex]
    property string currentPageTitle: ["Session Library", "Download Sessions", "About"][pageStack.currentIndex]
    property string navigationMode: compactNavigation ? "compact" : "expanded"
    property int topLevelPageCount: 1

    function navigateTo(destination) {
        const index = ["library", "download", "about"].indexOf(destination);
        if (index !== -1) {
            pageStack.currentIndex = index;
        }
    }

    LaptimerSessionBrowser {
        id: sharedSessionBrowser
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            Action { text: qsTr("Quit"); onTriggered: Qt.quit() }
        }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: Theme.spacingMedium
            anchors.rightMargin: Theme.spacingMedium
            spacing: Theme.spacingSmall

            Label {
                text: app.compactNavigation ? app.currentPageTitle : app.title
                font.bold: true
                Layout.fillWidth: true
            }

            Repeater {
                model: app.compactNavigation ? navigationModel : null

                delegate: navigationButton
            }
        }
    }

    ListModel {
        id: navigationModel

        ListElement { destination: "library"; label: QT_TR_NOOP("Session Library"); iconName: "library" }
        ListElement { destination: "download"; label: QT_TR_NOOP("Download Sessions"); iconName: "download" }
        ListElement { destination: "about"; label: QT_TR_NOOP("About"); iconName: "info" }
    }

    Component {
        id: navigationButton

        Button {
            required property string destination
            required property string label
            required property string iconName
            property bool selected: app.currentDestination === destination
            property bool compact: app.compactNavigation

            text: compact ? "" : qsTr(label)
            display: compact ? AbstractButton.IconOnly : AbstractButton.TextBesideIcon
            implicitWidth: compact ? 40 : 216
            implicitHeight: 40
            onClicked: app.navigateTo(destination)

            contentItem: RowLayout {
                spacing: Theme.spacingSmall

                FluentIcon {
                    iconName: parent.parent.iconName
                    Layout.alignment: Qt.AlignVCenter
                }

                Label {
                    text: parent.parent.text
                    color: Theme.textColor
                    visible: !parent.parent.compact
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter
                }
            }

            background: Rectangle {
                radius: 4
                color: parent.selected
                    ? Theme.usesDarkAppearance ? "#3B4B5C" : "#DCEBFA"
                    : parent.hovered ? Theme.surfaceMutedColor : "transparent"
            }

            ToolTip.visible: hovered && compact
            ToolTip.text: qsTr(label)
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Pane {
            visible: !app.compactNavigation
            Layout.fillHeight: true
            Layout.preferredWidth: 240
            padding: Theme.spacingMedium

            background: Rectangle {
                color: Theme.surfaceMutedColor
                border.color: Theme.borderColor
                border.width: 1
            }

            ColumnLayout {
                anchors.fill: parent
                spacing: Theme.spacingSmall

                Label {
                    text: qsTr("Navigation")
                    font.bold: true
                    Layout.bottomMargin: Theme.spacingExtraSmall
                }

                Repeater {
                    model: app.compactNavigation ? null : navigationModel

                    delegate: navigationButton
                }

                Item {
                    Layout.fillHeight: true
                }
            }
        }

        StackLayout {
            id: pageStack

            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: 0

            SessionLibraryPane {
                sessionBrowser: sharedSessionBrowser
            }

            SessionDownloadPane {
                sessionBrowser: sharedSessionBrowser
            }

            AboutPane {}
        }
    }
}
