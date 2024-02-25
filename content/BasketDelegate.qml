import QtQuick 2.15
import QtQuick.Controls 2.15
import Backend

AbstractButton {
    id: control
    property string iconPath: "images/cheri.png"
    required property int index // TODO: move logic in parent?

    implicitWidth: image.implicitWidth + leftPadding + rightPadding
    implicitHeight: image.implicitHeight + topPadding + bottomPadding

    Image {
        id: image
        source: iconPath
        anchors.fill: parent
        anchors.leftMargin: control.leftPadding
        anchors.rightMargin: control.rightPadding
        anchors.topMargin: control.topPadding
        anchors.bottomMargin: control.bottomPadding
        fillMode: Image.PreserveAspectFit
        mipmap: true
    }

    // TODO: move in the parent?
    onClicked: Backend.basket.remove(index)
}
