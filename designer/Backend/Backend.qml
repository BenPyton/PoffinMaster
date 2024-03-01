pragma Singleton
import QtQuick
import Qt.labs.qmlmodels // TableModel

QtObject {
    id: backend
    property string name: "Qml Mockup"
    property string version: "0.1.0"
    property string qtVersion: "6.6.1"
    property string author: "Beno\u00EEt Pelletier"
    property string license: "GPLv3"
    property string licenseUrl: "https://www.gnu.org/licenses/gpl-3.0.html"
    property string sourceUrl: "https://github.com/BenPyton/PoffinMaster"
    property bool debug: true

    property QtObject poffin: Poffin {}

    property ListModel basket: ListModel {
        onDataChanged: poffin.cook(basket)
        onRowsInserted: poffin.cook(basket)
        onRowsRemoved: poffin.cook(basket)
    }

    property ListModel berries: ListModel {
        ListElement {
            name: "cheri"
            iconPath: "images/berries/cheri.png"
            spicy: 10
            dry: 0
            sweet: 0
            bitter: 0
            sour: 0
            smoothness: 20
        }
        ListElement {
            name: "rawst"
            iconPath: "images/berries/rawst.png"
            spicy: 0
            dry: 0
            sweet: 0
            bitter: 10
            sour: 0
            smoothness: 30
        }
        ListElement {
            name: "pecha"
            iconPath: "images/berries/pecha.png"
            spicy: 0
            dry: 0
            sweet: 10
            bitter: 0
            sour: 0
            smoothness: 25
        }
        ListElement {
            name: "oran"
            iconPath: "images/berries/oran.png"
            spicy: 10
            dry: 10
            sweet: 0
            bitter: 10
            sour: 10
            smoothness: 35
        }
    }
}
