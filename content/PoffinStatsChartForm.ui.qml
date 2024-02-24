

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtCharts
import Backend

PolarChartView {

    //property alias chartData: chartData
    id: chart
    anchors.fill: parent
    legend.visible: false
    antialiasing: true

    backgroundColor: "transparent"
    ValuesAxis {
        id: axisAngular
        min: 0
        max: 5
        labelsVisible: false
        gridLineColor: "grey"
        lineVisible: false
        tickType: ValuesAxis.TicksFixed
        tickCount: 6
    }

    ValuesAxis {
        id: axisRadial
        min: -5
        max: 30
        labelsVisible: false
        lineVisible: false
        gridLineColor: "grey"
        tickType: ValuesAxis.TicksDynamic
        tickAnchor: 0
        tickCount: 6
    }

    VXYModelMapper {
        id: mapper
        model: Backend.poffin.stats
        series: line
        firstRow: 0
        xColumn: 0
        yColumn: 1
        //rowCount: 6
    }

    LineSeries {
        id: line
        axisAngular: axisAngular
        axisRadial: axisRadial
        color: Material.primary
        width: 5
    }


    /*transitions: Transition {
        NumberAnimation {
            property: "y"
            duration: 100
            easing.type: Easing.OutQuad
        }
    }*/
}
