import QtQuick 2.15
import QtQuick.Controls 2.15
import Backend

BerryButtonUI {
    id: control
    required property int index

    readonly property int _MaxBerry: 4

    onClicked: {
        if (Backend.basket.rowCount() < _MaxBerry)
        {
            Backend.basket.append(Backend.berries.get(index));
            clickedAnim.start();
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
}
