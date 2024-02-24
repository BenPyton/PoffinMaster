import QtQuick 2.15
import QtQuick.Controls 2.15
import Backend

BasketDelegateUI {
    id: controlUI
    required property int index
    swipe.onCompleted: Backend.basket.remove(index)

    states: [
        State {
            name: "PRESSED"
            when: controlUI.pressed
            PropertyChanges { target: controlUI; scale: 1.2 }
        }
    ]

    transitions: Transition {
        NumberAnimation {
            target: controlUI
            property: "scale"
            duration: 100
            easing.type: Easing.OutQuad
        }
    }
}
