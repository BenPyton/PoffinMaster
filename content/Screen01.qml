

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
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

        Label {
            id: poffinName
            text: Backend.poffin.name + " Poffin LV." + Backend.poffin.level
                  + " (x" + Backend.poffin.count + ")"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: smoothText.top
            font.pointSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Label {
            id: smoothText
            text: "Smoothness   " + Backend.poffin.smoothness
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: stats.top
            anchors.bottomMargin: page.columnSpacing * Screen.pixelDensity
            font.pointSize: 18
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        ListView {
            id: stats
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            height: contentItem.childrenRect.height
            implicitHeight: height
            spacing: 1 * Screen.pixelDensity
            orientation: ListView.Vertical
            interactive: false

            model: Backend.poffin.stats
            delegate: PoffinStatDelegate {
                required property int index
                required property string label
                required bonusText
                required value
                required property color color
                text: label
                maxValue: Backend.poffin.maxTotal
                backgroundColor: "transparent"
                anchors.right: parent.right
                anchors.left: parent.left
                labelWidth: 80
                barColor: color
            }
        }
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
        //Layout.fillWidth: true
        //Layout.preferredHeight: 10 * Screen.pixelDensity
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
    //}
}
