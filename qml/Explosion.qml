import QtQuick 2.0

Item {
    x: modelData.x
    y: modelData.y
    width: modelData.width
    height: modelData.height

    AnimatedImage {
        anchors.fill: parent
        source: modelData.imageSource
    }

    Timer {
        interval: 50
        running: true
        repeat: false

        onTriggered: modelData.imageSource = ""
    }
}
