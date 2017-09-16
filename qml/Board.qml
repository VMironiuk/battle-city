import QtQuick 2.0

Rectangle {
    Eagle { }

    Repeater {
        model: board.tilesProperty
        Tile { }
    }
    Repeater {
        model: board.playerTanksProperty
        PlayerTank { }
    }
    Repeater {
        model: board.enemyTanksProperty
        EnemyTank { }
    }
    Repeater {
        model: board.projectilesProperty
        Projectile { }
    }
    Repeater {
        model: board.explosionsProperty
        Explosion { }
    }
    Repeater {
        model: board.bonusesProperty
        Bonus { }
    }
}
