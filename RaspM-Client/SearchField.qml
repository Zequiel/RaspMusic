import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
        width: 135
        height: 20
        anchors.left: parent.left
        anchors.leftMargin: 7
        anchors.verticalCenter: parent.verticalCenter
        radius: 15
        border.color: "black"
        border.width: 1
        TextField {
                id: searchText
                x: 6
                width: 110
                height: 20
                placeholderText: qsTr("Search")
                font.pixelSize: 11
                textColor: "black"
                style: Rectangle {
                    border.width: 0
                }
                onTextChanged: getResult()
        }
        Image {
                id: searchImage
                width: 12
                height: 12
                opacity: 0.3
                anchors.top: parent.top
                anchors.topMargin: 4
                anchors.right: parent.right
                anchors.rightMargin: 5
                source: "icons/search.png"
        }
        function getResult() {
                var search = searchText.text;
                console.log(search);
        }
}
