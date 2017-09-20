import QtQuick 2.0
import battlecity.gameresult 1.0

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
        console.log("I - " + gameResult.totalPoints)
        console.log("Usual: points = " + gameResult.tankPoints(GameResult.Usual) + "; count = " + gameResult.tankCount(GameResult.Usual))
        console.log("TroopCarrier: points = " + gameResult.tankPoints(GameResult.TroopCarrier) + "; count = " + gameResult.tankCount(GameResult.TroopCarrier))
        console.log("Bursting: points = " + gameResult.tankPoints(GameResult.Bursting) + "; count = " + gameResult.tankCount(GameResult.Bursting))
        console.log("Armored: points = " + gameResult.tankPoints(GameResult.Armored) + "; count = " + gameResult.tankCount(GameResult.Armored))
        console.log("Total tanks count = " + gameResult.totalTankCount())
        gameResult.resetStage()
    }
}
