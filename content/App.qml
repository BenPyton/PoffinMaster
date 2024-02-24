// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QtQuick.Controls.Material
import PoffinMasterDS
import Backend

Window {
    width: Constants.width
    height: Constants.height

    //Material.theme: Material.Dark

    visible: true
    title: "Poffin Master"

    Screen01 {
        id: mainScreen
        width: parent.width
        height: parent.height

        Connections {
            target: Backend.poffin
            function onCooked() {
                console.log("Yay!")
            }
        }
    }
}

