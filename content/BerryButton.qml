import QtQuick 2.15
import QtQuick.Controls 2.15
import Backend

AbstractButton {
    id: control
    required property int index
    property string iconPath: "images/cheri.png"

    // TODO: remove that!
    readonly property int _MaxBerry: 4

    // Triggered when trying to add in a full basket
    // (will be removed with the onClicked delegate)
    signal error()

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

    // TODO: move it in parent?
    // Try to add in the basket
    onClicked: {
        if (Backend.basket.rowCount() < _MaxBerry)
        {
            Backend.basket.append(Backend.berries.get(index));
            clickedAnim.start();
        }
        else{
            errorAnim.start();
            error()
        }
    }

    SequentialAnimation {
        id: clickedAnim

        NumberAnimation {
            target: control
            property: "scale"
            to: 0.9
            duration: 50
            easing.type: Easing.OutSine
        }
        NumberAnimation {
            target: control
            property: "scale"
            to: 1.1
            duration: 50
            easing.type: Easing.InOutSine
        }
        NumberAnimation {
            target: control
            property: "scale"
            to: 1
            duration: 50
            easing.type: Easing.InSine
        }
    }

    SequentialAnimation {
        id: errorAnim
        NumberAnimation {
            target: image
            property: "rotation"
            to: 10
            duration: 30
            easing.type: Easing.OutSine
        }
        NumberAnimation {
            target: image
            property: "rotation"
            to: -10
            duration: 60
            easing.type: Easing.InOutSine
        }
        NumberAnimation {
            target: image
            property: "rotation"
            to: 10
            duration: 60
            easing.type: Easing.InOutSine
        }
        NumberAnimation {
            target: image
            property: "rotation"
            to: -10
            duration: 60
            easing.type: Easing.InOutSine
        }
        NumberAnimation {
            target: image
            property: "rotation"
            to: 0
            duration: 30
            easing.type: Easing.InSine
        }
    }
}
