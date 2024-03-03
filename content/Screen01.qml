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
import QtQuick.Controls 6.2
import QtQuick.Layouts
import QtQuick.Controls.Material
import PoffinMasterDS
import Backend

Page {
    id: page
    padding: 10
    clip: true

    readonly property real columnSpacing: 2

    Item {
        id: main
        implicitHeight: poffinName.height + smoothText.height + stats.height
        implicitWidth: Math.max(poffinName.width, smoothText.width)
        anchors.bottom: basket.top
        anchors.bottomMargin: page.columnSpacing * Screen.pixelDensity
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        visible: (Backend.poffin.type !== Poffin.Null)

        Image {
            id: poffinImage
            source: Backend.poffin.imageSource
            fillMode: Image.PreserveAspectFit
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: poffinName.top
            anchors.margins: 3 * Screen.pixelDensity
            smooth: false
            visible: height > 10 * Screen.pixelDensity
        }

        Label {
            id: poffinName
            //: The resulting poffin string. %1 is the poffin name (e.g. Rich, Sweet-Bitter, Foul) %2 is the poffin level, %3 is the number of poffin produced
            text: qsTr("%1 LV.%2 (x%3)").arg(Backend.poffin.name).arg(Backend.poffin.level).arg(Backend.poffin.count)
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: smoothText.top
            font.pointSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Label {
            id: smoothText
            //: The smoothness of the berry.
            text: qsTr("smoothness") + "   " + Backend.poffin.smoothness
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: stats.top
            anchors.bottomMargin: page.columnSpacing * Screen.pixelDensity
            font.pointSize: 18
            font.capitalization: Font.Capitalize
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        readonly property real statHeight: 3 * Screen.pixelDensity
        readonly property real statSpacing: 1 * Screen.pixelDensity
        readonly property real statFontSize: 1

        ListView {
            id: statsLabel
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: contentItem.childrenRect.width
            height: contentHeight
            spacing: main.statSpacing
            orientation: ListView.Vertical
            interactive: false

            model: Backend.poffin.stats
            delegate: Label {
                required property string label
                text: label
                //anchors.right: parent.right
                height: main.statHeight
                font.pixelSize: main.statFontSize * height
                font.capitalization: Font.Capitalize
                verticalAlignment: Text.AlignVCenter
            }
        }

        ListView {
            id: stats
            anchors.right: statsValue.left
            anchors.left: statsLabel.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 2 * main.statSpacing
            anchors.leftMargin: 2 * main.statSpacing
            height: contentItem.childrenRect.height
            spacing: main.statSpacing
            orientation: ListView.Vertical
            interactive: false

            model: Backend.poffin.stats
            delegate: PoffinStatDelegate {
                required property int index
                required value
                required property color color
                maxValue: Backend.poffin.level
                backgroundColor: "transparent"
                anchors.right: parent.right
                anchors.left: parent.left
                barColor: color
                height: main.statHeight
            }
        }

        ListView {
            id: statsValue
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: contentItem.childrenRect.width
            height: contentHeight
            spacing: main.statSpacing
            orientation: ListView.Vertical
            interactive: false

            model: Backend.poffin.stats
            delegate: Label {
                required property string bonusText
                required property real value
                text: "+" + value + " " + bonusText
                height: main.statHeight
                font.pixelSize: main.statFontSize * height
                font.capitalization: Font.Capitalize
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    Label {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: basket.top
        anchors.bottomMargin: page.columnSpacing * Screen.pixelDensity
        //: Text displayed when no berry is selected
        text: qsTr("Select a berry")
        opacity: 0.3
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 24
        visible: (Backend.poffin.type === Poffin.Null)
    }

    ListView {
        id: basket
        orientation: ListView.Horizontal
        width: 4 * (height + spacing) - spacing
        height: 12 * Screen.pixelDensity
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: berryList.top
        anchors.bottomMargin: page.columnSpacing * Screen.pixelDensity
        interactive: false

        model: Backend.basket

        delegate: BasketDelegate {
            required iconPath
            required index
            height: basket.height
            width: height
        }

        displaced: Transition {
            NumberAnimation {
                property: "x"
                easing.type: Easing.InOutQuad
            }
        }

        add: Transition {
            NumberAnimation {
                property: "scale"
                from: 0
                to: 1
                easing.type: Easing.OutBack
                duration: 200
            }
        }

        remove: Transition {
            ParallelAnimation {
                NumberAnimation {
                    property: "scale"
                    to: 1.5
                    easing.type: Easing.OutQuad
                    duration: 200
                }
                NumberAnimation {
                    property: "opacity"
                    to: 0
                    easing.type: Easing.OutQuad
                    duration: 200
                }
            }
        }
    }

    ListView {
        id: berryList
        flickableDirection: Flickable.HorizontalFlick
        orientation: ListView.Horizontal
        height: 10 * Screen.pixelDensity
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        model: Backend.berries

        delegate: BerryButton {
            required iconPath
            required index
            height: berryList.height
            width: height
        }
    }
}
