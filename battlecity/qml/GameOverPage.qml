import QtQuick 2.0

Item {
    id: root
    focus: true

    Image {
        anchors.fill: parent
        source: "qrc:/images/pages/game_over.png"
    }

    Loader {
        id: loader
        anchors.fill: parent
    }

    Keys.onReturnPressed: {
        loader.source = "StartPage.qml"
        loader.focus = true
        root.focus = false
    }
}
