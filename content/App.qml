/*
 * Copyright 2024 Benoit Pelletier
 *
 * This file is part of Poffin Master.
 * Poffin Master is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * Poffin Master is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Poffin Master. If not, see <https://www.gnu.org/licenses/>.
 */

import QtQuick 6.2
import QtQuick.Controls.Material
import PoffinMasterDS
import Backend

Window {
    id: window
    width: Constants.width
    height: Constants.height

    visible: true
    title: "poffin master"

    color: Material.primaryColor

    ToolBar {
        id: header
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        implicitHeight: title.height + 2 * padding

        padding: 10

        Label {
            id: title

            font.pixelSize: 5 * Screen.pixelDensity
            font.bold: true
            text: window.title
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.capitalization: Font.Capitalize
        }

        ToolButton {
            id: settings
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            //text: qsTr("Settings")
            //: Opens the 'about' popup
            text: qsTr("?")
            font.pixelSize: title.font.pixelSize
            //display: AbstractButton.IconOnly
            //icon.source: "icons/settings.png"
            //icon.color: "white"
            //icon.width: title.height
            //icon.height: title.height

            onClicked: popup.open()
        }

        Label {
            id: backendName
            visible: Backend.debug
            text: Backend.name
            anchors.left: parent.left
            anchors.top: parent.top
            padding: 0
            font.pointSize: 12
            font.italic: true
            font.family: Constants.font.family
        }
    }

    Screen01 {
        id: mainScreen
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left

        anchors.margins: 5
        anchors.topMargin: 0

        Connections {
            target: Backend.poffin
            function onCooked() {
                console.log("Yay!")
            }
        }
    }

    Label {
        id: resolutionText
        visible: Backend.debug
        opacity: 0.5
        anchors.top: mainScreen.top
        anchors.right: mainScreen.right
        anchors.topMargin: 1 * Screen.pixelDensity
        anchors.rightMargin: 1 * Screen.pixelDensity
        font.pointSize: 12
        font.bold: true
        text: window.width + " x " + window.height
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.Top
    }

    Dialog {
        id: popup
        anchors.centerIn: parent
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        standardButtons: Dialog.Ok
        font.pixelSize: 3 * Screen.pixelDensity

        header: Label {
            id: popupTitle
            text: qsTr("about")
            horizontalAlignment: Text.AlignHCenter
            padding: 1 * Screen.pixelDensity
            font.pixelSize: 4 * Screen.pixelDensity
            font.capitalization: Font.Capitalize
        }

        readonly property real textSpacing: 2 * Screen.pixelDensity
        readonly property string linkColor: "#20A0FF"

        contentWidth: mainText.width
        contentHeight: mainText.height + wrappingText.height + popup.textSpacing

        Label {
            id: mainText
            textFormat: Text.RichText
            text: qsTr("<b>Poffin Master</b> v%1
                <br/>Developed by %3
                <br/>Source code is under license <a href=\"%5\" style=\"color: %7;\">%4</a>
                <br/>Compiled with Qt %2
                <br/>Source code available on <a href=\"%6\" style=\"color: %7;\">Github</a>")
            .arg(Backend.version)
            .arg(Backend.qtVersion)
            .arg(Backend.author)
            .arg(Backend.license)
            .arg(Backend.licenseUrl)
            .arg(Backend.sourceUrl)
            .arg(popup.linkColor)

            onLinkActivated: (link) => Qt.openUrlExternally(link)

            HoverHandler {
                enabled: parent.hoveredLink
                cursorShape: Qt.PointingHandCursor
            }
        }

        Label {
            id: wrappingText
            anchors.top: mainText.bottom
            topPadding: popup.textSpacing
            text: qsTr("Berries and poffins images are used under the \"fair use\" and are owned by Game Freaks and ILCA.")
            wrapMode: Text.Wrap
            anchors.left: parent.left
            anchors.right: parent.right
        }

        Overlay.modal: Rectangle {
            color: "#80000000"

            Behavior on opacity {
                NumberAnimation {
                    duration: 120
                }
            }
        }
    }
}

