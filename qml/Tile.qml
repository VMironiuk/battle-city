import QtQuick 2.0

Item {
    x: modelData.x
    y: modelData.y
    width: modelData.width
    height: modelData.height

    Image {
        id: tileBackground
        anchors.fill: parent
        source: modelData.imageSource
    }
}
