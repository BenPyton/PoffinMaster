

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

Pane {
    id: page
    padding: 0

    Pane {
        id: header
        height: title.height + bottomPadding + topPadding
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        Material.background: Material.primary

        Label {
            id: title

            font.pointSize: 24
            font.bold: true
            text: "Poffin Master"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Label {
            id: test
            anchors.top: parent.top
            anchors.right: parent.right
            font.pointSize: 12
            font.bold: true
            text: page.width + " x " + page.height
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
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
            text: Backend.name
            anchors.left: parent.left
            anchors.top: versionName.bottom
            padding: 0
            font.pointSize: 12
            font.italic: true
            font.family: Constants.font.family
        }
    }

    ColumnLayout {
        id: column
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 10

        Item {
            id: main
            Layout.fillWidth: true
            Layout.fillHeight: true

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
                anchors.bottom: parent.bottom
                font.pointSize: 18
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Item {
            id: row
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumHeight: stats.height

            //Layout.fillHeight: true
            ListView {
                id: stats

                //anchors.top: row.top
                anchors.left: row.left
                anchors.right: basket.left

                //anchors.bottom: row.bottom
                height: contentItem.childrenRect.height
                implicitHeight: height
                spacing: 5
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

            ListView {
                id: basket
                verticalLayoutDirection: ListView.BottomToTop
                orientation: ListView.Vertical
                //Layout.fillWidth: true
                //Layout.fillHeight: true
                //Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                //Layout.maximumWidth: 60
                //Layout.minimumWidth: 60
                width: 60
                //height: 100
                anchors.top: row.top
                anchors.bottom: row.bottom
                anchors.right: row.right

                model: Backend.basket

                delegate: BasketDelegate {
                    required iconPath
                    required index
                    width: basket.width
                }

                displaced: Transition {
                    NumberAnimation {
                        property: "y"
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
            }
        }

        ListView {
            id: berryList
            flickableDirection: Flickable.HorizontalFlick
            orientation: ListView.Horizontal

            //implicitHeight: 60
            Layout.fillWidth: true
            //Layout.fillHeight: true
            Layout.maximumHeight: 60
            Layout.minimumHeight: 60

            model: Backend.berries
            delegate: BerryButton {
                required name
                required iconPath
                required index
                height: berryList.height
                width: height
            }
        }
    }
}
