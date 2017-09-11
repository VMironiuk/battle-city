import QtQuick 2.0

Item {
    x: board.eagle.x
    y: board.eagle.y
    width: board.eagle.width
    height: board.eagle.height

    Image {
        anchors.fill: parent
        source: board.eagle.imageSource
    }
}
