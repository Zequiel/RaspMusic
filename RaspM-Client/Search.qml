import QtQuick 2.0

Rectangle {
    id: searchLayout
    anchors.fill: parent
    width: 200
    height: 350
    ListView {
        id: menu
        width: parent.width
        height: parent.height - player.height
        delegate: Item {
            x: 5
            width: parent.height
            height: 40
            data: selectedState
            Row {
                id: row
                Image {
                    width: 40
                    height: 40
                    source: albumImage
                }
                Text {
                    text: title
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
                spacing: 10
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    content.state = menu.currentItem.data
                }
            }
        }
        model: ListModel {
            ListElement {
                title: "Historique"
                albumImage: "icons/history.png"
            }
        }
    }
    Rectangle {
        id: player
        width: parent.width
        height: parent.height * 0.1
        state: "PAUSE"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        Image {
            id: albumImage
            width: 28
            height: 28
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            source: ""
        }
        Text {
            text: title
            anchors.left: parent.left
            anchors.leftMargin: 48
            anchors.verticalCenter: parent.verticalCenter
        }
        Image {
            width: 28
            height: 28
            anchors.right: parent.right
            anchors.rightMargin: 70
            anchors.verticalCenter: parent.verticalCenter
            source: "icons/prevent.png"
        }
        Image {
            width: 28
            height: 28
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.verticalCenter: parent.verticalCenter
            source: "icons/play.png"
        }
        Image {
            width: 28
            height: 28
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
            source: "icons/next.png"
        }
    }
}
