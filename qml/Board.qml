import QtQuick 2.0

Rectangle {
    Repeater {
        model: board.tiles
        Tile { }
    }
    Repeater {
        model: board.tanks
        Tank { }
    }

    onWidthChanged: {
        board.width = width
    }
    onHeightChanged: {
        board.height = height
    }
}
