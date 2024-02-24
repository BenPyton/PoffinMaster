

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material

SwipeDelegate {
    id: element
    property string iconPath: "images/ceriz.png"

    width: 80
    height: width

    bottomPadding: 0
    topPadding: 0
    padding: 0
    contentItem: Image {
        source: element.iconPath
        width: element.width
        height: width
        opacity: 1 - Math.abs(element.swipe.position)
    }

    swipe.behind: Label {
        text: ""
        width: element.width
        height: element.height
    }

    //Material.roundedScale: Material.FullScale
    background: Rectangle {
        color: "#00000000"
    }

    Transition {
        id: pressedTransition
    }
}
