/*
 * Copyright 2024 Benoit Pelletier
 *
 * This file is part of Poffin Master.
 * Poffin Master is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * Poffin Master is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Poffin Master. If not, see <https://www.gnu.org/licenses/>.
 */

import QtQuick
//import Qt.labs.qmlmodels // TableModel

QtObject {
    enum Type {
        Null,
        Foul,
        Overripe,
        Normal,
        Rich,
        Mild,
        SuperMild
    }

    /*property TableModel statsChart: TableModel {
        TableModelColumn { display: "x" }
        TableModelColumn { display: "y" }
        rows: [
            {display: "Spicy", x:0, y:0},
            {display: "Dry", x:1, y:10},
            {display: "Sweet", x:2, y:20},
            {display: "Bitter", x:3, y:30},
            {display: "Sour", x:4, y:10},
            {display: "Spicy", x:5, y:0}
        ]
    }*/

    property ListModel stats: ListModel {
            ListElement {label: "Spicy"; key: 0; value: 0; bonusText: "Coolness"; color: "#f08030"}
            ListElement {label: "Dry"; key:1; value: 10; bonusText: "Beauty"; color: "#6890f0"}
            ListElement {label: "Sweet"; key:2; value: 20; bonusText: "Cuteness"; color: "#f85888"}
            ListElement {label: "Bitter"; key:3; value: 30; bonusText: "Cleverness"; color: "#78c850"}
            ListElement {label: "Sour"; key:4; value: 10; bonusText: "Toughness"; color: "#f8d030"}
    }

    property int smoothness: 0
    property int level: 0
    property int count: 0
    property int type: Poffin.Type.Null
    property string name: "Null"
    property string imageSource: "images/poffins/spicy-bitter.png"

    signal cooked() // called when a new poffin is cooked

    function cook(basket){
        let smoothSum = 0;
        let sums = [0,0,0,0,0];
        for (let i = 0; i < basket.count; ++i)
        {
            let berry = basket.get(i);
            sums[0] += berry.spicy - berry.dry;
            sums[1] += berry.dry - berry.sweet;
            sums[2] += berry.sweet - berry.bitter;
            sums[3] += berry.bitter - berry.sour;
            sums[4] += berry.sour - berry.spicy;
            smoothSum += berry.smoothness
        }
        smoothness = Math.floor(smoothSum / basket.count) - basket.count;

        let negativeCount = 0;
        for (let j = 0; j < sums.length; ++j)
        {
            negativeCount += (sums[j] < 0);
        }
        let nbFlavor = 0;
        let mainFlavor = 0;
        let subFlavor = 0;
        for (let l = 0; l < sums.length; ++l)
        {
            sums[l] = Math.max(0, Math.min(sums[l] - negativeCount, 100));
            nbFlavor += (sums[l] > 0);
            if (l > 0)
            {
                if (sums[l] > sums[mainFlavor])
                {
                    subFlavor = mainFlavor;
                    mainFlavor = l;
                }
                else if (subFlavor == mainFlavor || sums[l] > sums[subFlavor])
                    subFlavor = l;
            }
        }

        // Update the table model
        /*let model = backend.poffin.statsChart;
        for (let k = 0; k < model.rowCount; ++k)
        {
            model.setData(model.index(k, 1), "display", sums[k % sums.length]);
        }*/

        // Update list model
        level = 0
        for (let k = 0; k < stats.count; ++k)
        {
            let value = sums[k % sums.length];
            if (value > level)
                level = value;
            stats.setProperty(k, "value", value);
            //console.log("value: " + value + " (max: " + level + ")");
        }
        count = basket.count;

        // Update poffin type
        type = Poffin.Type.Normal;
        if (basket.count === 0)
            type = Poffin.Type.Null;
        else if (nbFlavor == 0)
            type = Poffin.Type.Overripe;
        else if (level >= 95)
            type = Poffin.Type.SuperMild;
        else if (level >= 50)
            type = Poffin.Type.Mild;
        else if (nbFlavor == 3)
            type = Poffin.Type.Rich;

        randomTimer.stop();
        // Update poffin name
        name = "None";
        switch (type)
        {
        case Poffin.Foul:
            level = 2;
            name = "Foul"
            randomTimer.start();
            break;
        case Poffin.Type.Normal:
            if (nbFlavor == 2)
                name = stats.get(mainFlavor).label + "-" + stats.get(subFlavor).label;
            else
                name = stats.get(mainFlavor).label;
            break;
        case Poffin.Type.Overripe:
            level = 2;
            name = "Overripe";
            randomTimer.start();
            break;
        case Poffin.Type.Rich:
            name = "Rich";
            break;
        case Poffin.Type.Mild:
            name = "Mild";
            break;
        case Poffin.Type.SuperMild:
            name = "Super Mild";
            break;
        }



        //console.log("Poffin cooked!");
        cooked();
    }

    property Timer randomTimer: Timer {
        //id: randomTimer
        triggeredOnStart: true
        interval: 1000
        repeat: true

        onTriggered: {
            setRandomStats();
        }
    }

    function setRandomStats()
    {
        let nbRandomStat = 1;
        let statIndices = [0, 1, 2, 3, 4];
        if (type === Poffin.Foul)
            nbRandomStat = 2;
        else if (type === Poffin.Overripe)
            nbRandomStat = 3;

        while (nbRandomStat < statIndices.length)
        {
            let i = Math.floor(statIndices.length * Math.random());
            console.log("Take out " + i + " | " + nbRandomStat);
            statIndices.splice(i, 1);
            //++nbRandomStat;
        }

        for(let i = 0; i < 5; ++i)
        {
            stats.setProperty(i, "value", (statIndices.indexOf(i) < 0) ? 0 : 2);
        }
    }
}
