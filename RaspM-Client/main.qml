import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    id: mainElement
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    signal send()
    signal connect()
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Text {
        id: addSource
        text: qsTr("Send data !")
        visible: false
        anchors.centerIn: parent

        MouseArea {
            id: clickArea
            anchors.fill: parent
            onClicked: mainElement.send()
        }
    }

    Button {
        id: connect
        x: 280
        y: 143
        text: "Connect !"
        onClicked: {
            mainElement.connect();
            addSource.visible = true;
        }
    }
}
