import QtQuick 2.0

ListView {
    anchors.top: content.bottom
    anchors.topMargin: 0
    x: 80
    width: parent.width
    height: 132
    snapMode: ListView.SnapToItem
    focus: true
    delegate: Item {
        x: 5
        width: 80
        height: 20
        Row {
            spacing: 10
            Text {
                text: name
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: sendQueryToReadMusic(name)
        }
    }
    model: ListModel {
        id: musicListModel
    }

    function sendQueryToReadMusic(name) {

    }
}
