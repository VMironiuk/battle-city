import QtQuick 2.0

Rectangle {
    Repeater {
        model: board.tilesProperty
        Tile { }
    }
    Repeater {
        model: board.playerTanksProperty
        PlayerTank { }
    }
    Repeater {
        model: board.projectilesProperty
        Projectile { }
    }
}
