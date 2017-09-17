import QtQuick 2.0

Item {
    id: root
    focus: true

    Image {
        anchors.fill: parent
        source: "qrc:/images/pages/stage_result.png"
    }

    Loader {
        id: loader
        anchors.fill: parent
    }

    Keys.onReturnPressed: {
        if (gameController.won == true) {
            gameController.setupStage()
            loader.source = "StagePage.qml"
            loader.focus = true
            root.focus = false
        } else {
            loader.source = "GameOverPage.qml"
            loader.focus = true
            root.focus = false
        }
    }

    Component.onCompleted: {
        gameController.stopStage()
    }
}
