import QtQuick 2.0

Item {
    id: root
    focus: true

    Rectangle {
        id: topRect
        width: parent.width
        height: parent.height * 0.5
        color: "gray"
    }

    Rectangle {
        id: bottomRect
        width: parent.width
        height: parent.height * 0.5
        color: "gray"
    }

    Text {
        id: stageText
        visible: false
        anchors.centerIn: parent
        font.pixelSize: 24
        font.family: "Console"
        text: qsTr("S T A G E  " + informationPanel.stageNo)
    }

    ParallelAnimation {
        running: true

        onStopped: {
            stageText.visible = true
        }

        NumberAnimation {
            target: topRect
            property: "y"
            from: root.y - topRect.height
            to: 0
            duration: 100
        }

        NumberAnimation {
            target: bottomRect
            property: "y"
            from: root.height
            to: parent.height * 0.5
            duration: 100
        }
    }

    Loader {
        id: loader
        anchors.fill: parent
        width: parent.width
        height: parent.height
    }

    Keys.onReturnPressed: {
        loader.source = "Playground.qml"
        loader.focus = true
        root.focus = false
    }
}
