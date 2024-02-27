

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Controls.Material

Rectangle {
    id: background

    property alias barColor: bar.color
    property alias backgroundColor: background.color

    property real value: 50
    property real maxValue: 100

    color: Material.background
    radius: 3
    implicitWidth: 100
    implicitHeight: 30

    Rectangle {
        id: bar
        color: Material.accent
        radius: background.radius
        width: (background.maxValue > 0) ? background.width * background.value / background.maxValue : 0
        anchors.top: background.top
        anchors.bottom: background.bottom
        anchors.left: background.left

        Behavior on width {
            NumberAnimation {
                duration: 500
                easing.type: Easing.OutQuad
            }
        }
    }
}
