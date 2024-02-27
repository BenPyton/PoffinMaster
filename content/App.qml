// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QtQuick.Controls.Material
import PoffinMasterDS
import Backend

Window {
    id: window
    width: Constants.width
    height: Constants.height

    visible: true
    title: "Poffin Master"

    color: Material.primaryColor

    ToolBar {
        id: header
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        implicitHeight: title.height + 2*padding

        padding: 10

        Label {
            id: title

            font.pixelSize: 5 * Screen.pixelDensity
            font.bold: true
            text: window.title
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        /*ToolButton {
            id: settings
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            text: qsTr("Settings")
            display: AbstractButton.IconOnly
            icon.source: "icons/settings.png"
            icon.color: "white"
            icon.width: title.height
            icon.height: title.height
        }*/
        Label {
            id: versionName
            text: Backend.version
            anchors.left: parent.left
            anchors.top: parent.top
            padding: 0
            font.pointSize: 12
            font.family: Constants.font.family
        }

        Label {
            id: backendName
            visible: Backend.debug
            text: Backend.name
            anchors.left: parent.left
            anchors.top: versionName.bottom
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
}

