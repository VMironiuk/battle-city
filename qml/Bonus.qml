import QtQuick 2.0

Item {
    x: modelData.x
    y: modelData.y
    width: modelData.width
    height: modelData.height

    Image {
        anchors.fill: parent
        source: modelData.imageSource
    }
}
