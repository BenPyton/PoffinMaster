pragma Singleton
import QtQuick
import Qt.labs.qmlmodels // TableModel

QtObject {
    id: backend
    property string name: "Qml Mockup"
    property string version: "v0.1.0"

    property QtObject poffin: Poffin {}

    property ListModel basket: ListModel {
        onDataChanged: poffin.cook(basket)
        onRowsInserted: poffin.cook(basket)
        onRowsRemoved: poffin.cook(basket)
    }

    property ListModel berries: ListModel {
        ListElement {
            name: "mCeriz"
            iconPath: "images/cheri.png"
            spicy: 10
            dry: 0
            sweet: 0
            bitter: 0
            sour: 0
            smoothness: 20
        }
        ListElement {
            name: "mFraive"
            iconPath: "images/rawst.png"
            spicy: 0
            dry: 0
            sweet: 0
            bitter: 10
            sour: 0
            smoothness: 30
        }
        ListElement {
            name: "mPecha"
            iconPath: "images/pecha.png"
            spicy: 0
            dry: 0
            sweet: 10
            bitter: 0
            sour: 0
            smoothness: 25
        }
        ListElement {
            name: "mOran"
            iconPath: "images/oran.png"
            spicy: 10
            dry: 10
            sweet: 0
            bitter: 10
            sour: 10
            smoothness: 35
        }
    }
}
