import QtQuick 2.6
import QtQuick.Window 2.2
import battlecity.movableitem 1.0

Window {
    visible: true
    color: "black"
    maximumWidth: 1024
    minimumWidth: 1024
    maximumHeight: 896
    minimumHeight: 896

    Loader {
        anchors.fill: parent
        source: "StartPage.qml"
        focus: true
    }
}
