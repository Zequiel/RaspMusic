import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1

Rectangle {
    id: header
    width: parent.width
    height: parent.height * 0.08
    property variant menus: []
    property MusicList musicList: null
    signal stateChanged(string stateName)

    Button {
        id: menuButton
        width: parent.height
        height: parent.height
        anchors.right: parent.right
        anchors.rightMargin: 0
        checkable: true
        anchors.top: parent.top
        anchors.topMargin: 0
        style: ButtonStyle {
            background: Image {
                width: parent.height * 0.8
                height: parent.height * 0.8
                source: "icons/menu.png"
            }
        }
    }
    Rectangle {
        parent: header.parent
        width: parent.width * 0.2
        height: (parent.height * 0.08) * menus.length
        z: 2
        anchors.top: header.bottom
        anchors.right: header.right
        visible: menuButton.checked

        ListView {
            snapMode: ListView.SnapToItem
            width: parent.width
            height: parent.height
            focus: true
            delegate: Item {
                property string state: state
                width: parent.width
                height: parent.parent.height * (1 / menus.length)
                Row {
                    anchors.fill: parent
                    spacing: parent.height * 0.01
                    Image {
                        width: parent.height
                        height: parent.height
                        source: image
                    }
                    Text {
                        text: title
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: changeState(title.toUpperCase())
                }
            }
            model: ListModel {
                id: menuListModel
            }
        }
    }

    SearchField {
    }

    function changeState(state) {
        menuButton.checked = false;
        stateChanged(state);
    }

    Component.onCompleted: {
        for (var i = 0; i < menus.length; ++i) {
            var menu = menus[i];

            menuListModel.append({
                                     title: menu.title,
                                     image: menu.image,
                                     state: menu.state
                                 });
        }
    }
}
