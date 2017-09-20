import QtQuick 2.0
import battlecity.gameresult 1.0

Rectangle {
    id: root
    color: "black"
    focus: true

    Grid {
        columns: 1
        spacing: 25
        anchors.centerIn: parent

        // HI-SCORE
        Text {
            text: "HI-SCORE " + "<font color=\"#ce6306\">20000</font>"
            color: "white"
            font.pixelSize: 36
            font.bold: true
        }

        // STAGE
        Text {
            text: "STAGE  " + informationPanel.stageNo
            color: "white"
            font.pixelSize: 36
            font.bold: true
        }

        // I-PLAYER
        Text {
            text: "I-PLAYER " + "<font color=\"#ce6306\">" + gameResult.totalPoints + "</font>"
            color: "white"
            font.pixelSize: 36
            font.bold: true
        }

        Grid {
            columns: 4
            spacing: 25

            Column {
                Text {
                    text: gameResult.tankPoints(GameResult.Usual)
                    color: "white"
                    font.pixelSize: 36
                    font.bold: true
                }
                Text {
                    text: gameResult.tankPoints(GameResult.TroopCarrier)
                    color: "white"
                    font.pixelSize: 36
                    font.bold: true
                }
                Text {
                    text: gameResult.tankPoints(GameResult.Bursting)
                    color: "white"
                    font.pixelSize: 36
                    font.bold: true
                }
                Text {
                    text: gameResult.tankPoints(GameResult.Armored)
                    color: "white"
                    font.pixelSize: 36
                    font.bold: true
                }
            }

            Column {
                Repeater {
                    model: 4
                    delegate: Text {
                        text: "PTS"
                        color: "white"
                        font.pixelSize: 36
                        font.bold: true
                    }
                }
            }

            Column {
                Text {
                    text: gameResult.tankCount(GameResult.Usual)
                    color: "white"
                    font.pixelSize: 36
                    font.bold: true
                }
                Text {
                    text: gameResult.tankCount(GameResult.TroopCarrier)
                    color: "white"
                    font.pixelSize: 36
                    font.bold: true
                }
                Text {
                    text: gameResult.tankCount(GameResult.Bursting)
                    color: "white"
                    font.pixelSize: 36
                    font.bold: true
                }
                Text {
                    text: gameResult.tankCount(GameResult.Armored)
                    color: "white"
                    font.pixelSize: 36
                    font.bold: true
                }
            }

            Column {
                spacing: 10
                Image {
                    width: 42
                    height: 42
                    source: "qrc:/images/tanks/enemy/simple_tank.png"
                }
                Image {
                    width: 42
                    height: 42
                    source: "qrc:/images/tanks/enemy/fast.png"
                }
                Image {
                    width: 42
                    height: 42
                    source: "qrc:/images/tanks/enemy/bursting.png"
                }
                Image {
                    width: 42
                    height: 42
                    source: "qrc:/images/tanks/enemy/armored.png"
                }
            }
        }

        Row {
            spacing: 50
            Text {
                text: "Total"
                color: "white"
                font.pixelSize: 36
                font.bold: true
            }
            Text {
                text: gameResult.totalTankCount()
                color: "white"
                font.pixelSize: 36
                font.bold: true
            }
        }
    }

    Loader {
        id: loader
        anchors.fill: parent
    }

    Keys.onReturnPressed: {
        if (gameController.won == true) {
            if (gameController.setupStage() === true) {
                loader.source = "StagePage.qml"
                loader.focus = true
                root.focus = false
            } else {
                console.log(gameController.errorString)
                // TODO: show error
            }
        } else {
            loader.source = "GameOverPage.qml"
            loader.focus = true
            root.focus = false
        }
    }

    Component.onCompleted: {
        gameController.stopStage()
        gameResult.resetStage()
    }
}

