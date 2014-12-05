import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    id: mainElement
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    signal send(string url)
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
        anchors.verticalCenterOffset: 107
        anchors.horizontalCenterOffset: 1
        visible: false
        anchors.centerIn: parent

        MouseArea {
            id: clickArea
            anchors.fill: parent
            onClicked: mainElement.send(url.text)
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

    TextInput {
        id: url
        x: 47
        y: 207
        width: 557
        height: 20
        text: qsTr("url")
        font.pixelSize: 12
    }
}
