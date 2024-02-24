import QtQuick 2.15
import Backend

PoffinStatsChartForm {
    Connections {
        target: Backend
        /*function onPoffinUpdated() {
            let tastes = [];
            tastes.push(Backend.poffin.totalSpicy);
            tastes.push(Backend.poffin.totalDry);
            tastes.push(Backend.poffin.totalSweet);
            tastes.push(Backend.poffin.totalBitter);
            tastes.push(Backend.poffin.totalSour);

            console.log("Chart Update!");
            for (let i = 0; i < chartData.count; ++i)
            {
                let point = chartData.at(i);
                let newValue = tastes[i % tastes.length];

                chartData.at(i).y = newValue;
                //chartData.replace(point.x, point.y, point.x, newValue);
                animPoint.from = point.y;
                animPoint.to = newValue;
                //animPoint.target(chartData.at(i));
                animPoint.start();
            }
        }*/
    }

    NumberAnimation {
        id: animPoint
        //target: chartData
        property: "y"
        duration: 500
        easing.type: Easing.OutQuad
    }
}
