import QtQuick 2.0

Rectangle {
    Repeater {
        model: board.tiles
        Tile { }
    }

    onWidthChanged: {
        board.width = width
    }
    onHeightChanged: {
        board.height = height
    }
}
