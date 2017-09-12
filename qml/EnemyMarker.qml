import QtQuick 2.0

Item {
    width: 32
    height: 32

    Image {
        anchors.fill: parent
        source: modelData.imageSource
    }
}
