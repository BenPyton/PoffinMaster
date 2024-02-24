

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: stat

    implicitHeight: label.height

    //height: label.height
    property alias barColor: bar.color
    property alias backgroundColor: background.color
    property alias text: label.text
    property alias labelWidth: label.width

    property real value: 50
    property real maxValue: 100
    property string bonusText: "Beauty"

    Label {
        id: label
        text: "Label"
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 12
        font.bold: true
        width: 100
    }

    Rectangle {
        id: background
        color: Material.background
        anchors.left: label.right
        anchors.right: bonus.left
        anchors.top: stat.top
        anchors.bottom: stat.bottom
        anchors.leftMargin: 5
        anchors.rightMargin: 5
    }

    Rectangle {
        id: bar
        color: Material.accent
        implicitWidth: 100
        width: background.width * value / Math.max(10, maxValue)
        radius: 3
        anchors.top: background.top
        anchors.bottom: background.bottom
        anchors.left: background.left
    }

    Label {
        id: bonus
        text: "+" + Math.round(stat.value) + " " + stat.bonusText
        anchors.right: stat.right
        anchors.top: stat.top
        anchors.bottom: stat.bottom
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        font.weight: Font.Bold
        font.pointSize: label.font.pointSize
        width: 150
    }
}
