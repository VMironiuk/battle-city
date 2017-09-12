import QtQuick 2.0

Item {
    Item {
        anchors.top: parent.top
        Grid {
            columns: 2
            rows: informationPanel.maxEnemiesCount / 2
            spacing: 0
            Repeater {
                model: informationPanel.enemyMarkersProperty
                EnemyMarker { }
            }
        }
    }
}
