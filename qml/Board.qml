import QtQuick 2.0

Rectangle {
    onWidthChanged: {
        board.width = width
    }
    onHeightChanged: {
        board.height = height
    }
}
