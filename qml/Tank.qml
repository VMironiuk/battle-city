import QtQuick 2.0

Item {
    id: tank
    x: modelData.x
    y: modelData.y
    width: modelData.width
    height: modelData.height
    rotation: modelData.rotation
    focus: true

    Image {
        anchors.fill: parent
        source: modelData.imageSource
    }

    Keys.onUpPressed: {
        modelData.moveNorth()
    }
    Keys.onRightPressed: {
        modelData.moveEast()
    }
    Keys.onDownPressed: {
        modelData.moveSouth()
    }
    Keys.onLeftPressed: {
        modelData.moveWest()
    }
}
