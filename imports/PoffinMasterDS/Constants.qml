pragma Singleton
import QtQuick 6.2
import QtQuick.Studio.Application
import QtQuick.Controls.Material

QtObject {
    readonly property int width: 640
    readonly property int height: 480

    property string relativeFontDirectory: "fonts"

    /* Edit this comment to add your custom font */
    readonly property font font: Qt.font({
                                             family: Qt.application.font.family,
                                             pixelSize: Qt.application.font.pixelSize
                                         })
    readonly property font largeFont: Qt.font({
                                                  family: Qt.application.font.family,
                                                  pixelSize: Qt.application.font.pixelSize * 1.6
                                              })

    readonly property color gridColor: Material.color(Material.Green, Material.Shade500)
    readonly property color gridColor2: Material.color(Material.Green, Material.ShadeA700)

    property StudioApplication application: StudioApplication {
        fontPath: Qt.resolvedUrl("../../content/" + relativeFontDirectory)
    }
}
