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
}
