import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: playground
    color: "gray"

    RowLayout {
        anchors.fill: parent
        anchors.margins: 32
        spacing: 0

        Board {
            color: "black"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        InformationPanel {
            border.width: 1
            color: playground.color
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 128
            Layout.maximumWidth: 128
        }
    }
}
