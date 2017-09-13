import QtQuick 2.0

Item {
    id: root

    Item {
        id: enemies
        anchors.top: parent.top

        Grid {
            id: enemiesGrid
            columns: 2
            rows: informationPanel.maxEnemiesCount / 2
            spacing: 0
            Repeater {
                model: informationPanel.enemyMarkersProperty
                EnemyMarker { }
            }
        }
    }

    Item {
        id: bottomPart
        width: bottomPartColumn.width
        height: bottomPartColumn.height
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50

        Column {
            id: bottomPartColumn
            spacing: 50

            Item {
                id: playerIlives
                width: playerIGrid.width
                height: playerIGrid.height

                Grid {
                    id: playerIGrid
                    columns: 2
                    spacing: 1

                    Text { text: "I"; font.pixelSize: 50; color: "black"; font.bold: true }
                    Text { text: "P"; font.pixelSize: 50; color: "black"; font.bold: true }
                    Image { source: "qrc:/images/control_panel/player_marker.png"; width: 32; height: 32 }
                    Text { text: informationPanel.livesCount; font.pixelSize: 20; color: "black"; font.bold: true; }
                }
            }

            Item {
                id: stageNo
                width: stageNoColumn.width
                height: stageNoColumn.height

                Column {
                    id: stageNoColumn

                    Image { source: "qrc:/images/control_panel/flag.png" }
                    Grid {
                        columns: 2

                        Text { text: "     "; font.pixelSize: 25; }
                        Text { text: informationPanel.stageNo; font.pixelSize: 20; color: "black"; font.bold: true }
                    }
                }
            }
        }
    }
}
