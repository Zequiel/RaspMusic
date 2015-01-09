import QtQuick 2.0

Rectangle {
    property string content
    property string image
    signal clicked
    width: 100
    height: 32
    color: "#00000000"

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked()
    }

    Image {
        width: 32
        height: 32
        source: image
    }
    Text {
        height: 32
        anchors.left: parent.left
        anchors.leftMargin: 32
        text: content
    }
}
