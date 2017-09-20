import QtQuick 2.0

Rectangle {
    id: root
    focus: true
    color: "black"
    property bool stageCompleted: false

    Grid {
        anchors.centerIn: parent
        spacing: 100
        columns: 1

        Text {
            text: "I -    " + "<font color=\"#ce6306\">" + gameResult.totalPoints + "</font>" + "  HI -    20000"
            color: "white"
            font.pixelSize: 36
            font.bold: true
        }

        Image {
            source: "qrc:/images/pages/start.png"
        }

        Text {
            text: "<font color=\"red\"><b>Enter</b></font> - Pause/Continue
                   <br><font color=\"red\"><b>X</b></font> - Shot"
            color: "white"
            font.pixelSize: 24
        }
    }

    NumberAnimation on y {
        from: 800
        to: 0
        duration: 3000

        onStopped: {
            if (gameController.setupStage() === true) {
                stageCompleted = true
                gameResult.resetAll()
            } else {
                console.log(gameController.errorString)
                // TODO: else show error
            }
        }
    }

    Loader {
        id: loader
        anchors.fill: parent
    }

    Keys.onReturnPressed: {
        if (stageCompleted == true) {
            loader.source = "StagePage.qml"
            loader.focus = true
            root.focus = false
        }
    }
}
