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
