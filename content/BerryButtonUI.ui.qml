

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material

RoundButton {
    property string name: "Test Button"
    property string iconPath: "images/ceriz.png"

    id: control
    text: name
    icon.color: "#00000000"
    icon.source: iconPath
    icon.height: control.height
    icon.width: control.height
    display: AbstractButton.IconOnly
    radius: 1000
    padding: 0

    Material.background: Material.primary
}
