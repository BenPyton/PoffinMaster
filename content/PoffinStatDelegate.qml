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

import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Controls.Material

Rectangle {
    id: background

    property alias barColor: bar.color
    property alias backgroundColor: background.color

    property real value: 50
    property real maxValue: 100

    color: Material.background
    radius: 3
    implicitWidth: 100
    implicitHeight: 30

    Rectangle {
        id: bar
        color: Material.accent
        radius: background.radius
        width: (background.maxValue > 0) ? background.width * background.value / background.maxValue : 0
        anchors.top: background.top
        anchors.bottom: background.bottom
        anchors.left: background.left

        Behavior on width {
            NumberAnimation {
                duration: 500
                easing.type: Easing.OutQuad
            }
        }
    }
}
