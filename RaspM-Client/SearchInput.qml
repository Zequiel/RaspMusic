import QtQuick 2.0

Rectangle {
    id: search
    x:0
    width: 160
    height: 16
    anchors.top: parent.top
    anchors.topMargin: (parent.height / 2) - (this.height / 2)
    border.color: "black"
    border.width: 1
    radius: 15

    TextInput {
        id: searchText
        width: parent.width - 12
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 5
        verticalAlignment: Text.AlignVCenter
        inputMethodHints: "ImhNoPredictiveText"
        text: qsTr("Search")
        font.pixelSize: 12
        onAccepted: getResult()
    }

    Image {
        id: searchImage
        width: 12
        height: 12
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 5
        verticalAlignment: Image.AlignVCenter
        source: "icons/search.png"
    }

    function getResult() {
        var search = searchText.text;
    }
}

