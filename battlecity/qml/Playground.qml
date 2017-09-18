import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: playground
    color: "gray"

    RowLayout {
        anchors.fill: parent
        anchors.topMargin: 32
        anchors.leftMargin: 32
        anchors.bottomMargin: 32
        anchors.rightMargin: 0
        spacing: 32

        Board {
            id: boardItem
            color: "black"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        InformationPanel {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 128
            Layout.maximumWidth: 128
        }
    }

    Component.onCompleted: {
        gameController.startStage()
    }

    Keys.onReturnPressed: {
        console.log("playground: return pressed");
    }

    Loader {
        id: loader
        anchors.fill: parent
    }

    Component {
        id: gameOverComponent

        Text {
            id: gameOverText
            text: "GAME OVER"
            color: "red"
            font.pixelSize: 24
            font.bold: true
            x: boardItem.width / 2 - 40
            y: playground.height - 20

            NumberAnimation {
                running: true
                target: gameOverText
                property: "y"
                from: boardItem.height
                to: boardItem.height * 0.5
                duration: 3000

                onStopped: {
                    loader.source = "StageResultPage.qml"
                    loader.focus = true
                    playground.focus = false
                    gameController.freeStage()
                }
            }
        }
    }

    Connections {
        target: gameController
        onStageFinished: {
            if (gameController.won == false) {
                loader.sourceComponent = gameOverComponent
            } else {
                loader.source = "StageResultPage.qml"
                loader.focus = true
                playground.focus = false
            }

        }
    }
}
