import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    id: mainElement
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    signal clickedSig()
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
        text: qsTr("Hello World")
        anchors.centerIn: parent

        MouseArea {
            id: clickArea
            anchors.fill: parent
            onClicked: mainElement.clickedSig()
        }
    }
}