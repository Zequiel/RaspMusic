import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.2


ApplicationWindow {
    id: mainLayer
    visible: true
    width: Screen.width
    height: Screen.height
    Rectangle {
        id: content
        width: mainLayer.width
        height: mainLayer.height - nav.height
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        state: "NORMAL"
        children: [ Search { width: parent.width; height: parent.height } ]
        states: [
            State {
                name: "SEARCH"
                PropertyChanges {
                    target: content
                }
            },
            State {
                name: "HISTORY"
                PropertyChanges {
                    target: content
                }
            },
            State {
                name: "PLAYLISTS"
                PropertyChanges {
                    target: content
                }
            },
            State {
                name: "FAVORIES"
                PropertyChanges {
                    target: content
                }
            },
            State {
                name: "PROFILE"
                PropertyChanges {
                    target: content
                }
            }

        ]
    }

    Rectangle {
        id: nav
        width: mainLayer.width
        height: mainLayer.height * 0.1
        TextInput {
            id: searchInput
            width: 120
            height: 14
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
            font.family: "Times New Roman"
            anchors.left: parent.left
            anchors.leftMargin: 20
            horizontalAlignment: Text.AlignLeft
        }
        Button {
            id: menuButton
            width: menuButton.height * 0.9
            iconSource: "icons/menu.png"
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            onClicked: {
                menu.visible = !menu.visible
            }

            ListView {
                id: menu
                x: -(menu.width + 5)
                width: parent.width * 0.2
                height: parent.height * 0.2
                visible: false
                anchors.top: parent.bottom
                anchors.topMargin: -1
                anchors.right: parent.right
                anchors.rightMargin: 117
                cacheBuffer: 312
                delegate: Item {
                    x: 5
                    width: 80
                    height: 40
                    data: selectedState
                    Row {
                        id: row
                        Image {
                            width: 40
                            height: 40
                            source: sourceImage
                        }
                        Text {
                            text: name
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
                        name: "Historique"
                        sourceImage: "icons/history.png"
                        selectedState: "HISTORY"
                    }
                    ListElement {
                        name: "Playlists"
                        sourceImage: "icons/playlist.png"
                        selectedState: "PLAYLISTS"
                    }
                    ListElement {
                        name: "Favoris"
                        sourceImage: "icons/star.png"
                        selectedState: "FAVORIES"
                    }
                    ListElement {
                        name: "Profile"
                        sourceImage: "icons/profile.png"
                        selectedState: "PROFILE"
                    }
                }
            }
        }
    }
}


