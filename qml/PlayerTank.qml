import QtQuick 2.0
import battlecity.movableitem 1.0

Item {
    id: playerTank
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

    Keys.onPressed: {
        if (event.key === Qt.Key_Up) {
            modelData.direction = MovableItem.North
            modelData.movement = true
            event.accepted = true
        } else if (event.key === Qt.Key_Down) {
            modelData.direction = MovableItem.South
            modelData.movement = true
            event.accepted = true
        } else if (event.key === Qt.Key_Left) {
            modelData.direction = MovableItem.West
            modelData.movement = true
            event.accepted = true
        } else if (event.key === Qt.Key_Right) {
            modelData.direction = MovableItem.East
            modelData.movement = true
            event.accepted = true
        } else if (event.key === Qt.Key_X) {
            modelData.shoot()
            event.accepted = true
        }
    }

    Keys.onReleased: {
        modelData.movement = false
        event.accepted = true;
    }
}
