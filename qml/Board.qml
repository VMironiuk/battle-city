import QtQuick 2.0

Rectangle {
    Repeater {
        model: board.tilesProperty
        Tile { }
    }
    Repeater {
        model: board.tanksProperty
        Tank { }
    }

    onWidthChanged: {
        board.width = width
    }
    onHeightChanged: {
        board.height = height
    }
}
