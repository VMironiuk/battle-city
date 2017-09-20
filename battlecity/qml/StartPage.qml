import QtQuick 2.0

Item {
    id: root
    focus: true
    property bool stageCompleted: false

    Rectangle {
        color: "black"
        anchors.fill: parent

        Image {
            x: parent.width / 2 - width / 2
            y: parent.height / 2
            source: "qrc:/images/pages/start.png"

            NumberAnimation on y {
                from: 800
                to: 200
                duration: 3000

                onStopped: {
                    if (gameController.setupStage() === true) {
                        stageCompleted = true
                        console.log("I - " + gameResult.totalPoints)
                        gameResult.resetAll()
                    } else {
                        console.log(gameController.errorString)
                    // TODO: else show error
                    }
                }
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
