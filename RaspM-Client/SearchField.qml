import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
    id: search
    anchors.verticalCenter: parent.verticalCenter
    width: parent.width * 0.7
    height: parent.height * 0.7
    Rectangle {
        id: searchField
        objectName: "searchField"
        width: parent.width
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 7
        signal suggest(string query)
        signal search(string query)
        radius: 15
        border.color: "black"
        border.width: 1
        TextField {
            id: searchText
            x: parent.width * 0.02
            width: parent.width - (searchText.x + searchImage.width
                                   + searchImage.anchors.rightMargin)
            height: parent.height
            placeholderText: qsTr("Search")
            font.pixelSize: parent.height * 0.8
            textColor: "black"
            style: Rectangle {
                border.width: 0
            }
            onTextChanged: sendQuerySuggest()
        }
        Image {
            id: searchImage
            width: parent.height - 2
            height: parent.height - 2
            opacity: 0.3
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.02
            source: "icons/search.png"
        }

        Connections {
            target: client
            onSuggestResultReady: setSuggestResult(query, results)
        }
    }
    Rectangle {
        parent: search.parent
        width: search.width
        height: parent.parent.height * 0.4
        x: searchField.x
        z: 2
        anchors.top: parent.bottom
        visible: suggestListModel.count > 0
        ListView {
            snapMode: ListView.SnapToItem
            width: parent.width
            height: parent.height
            focus: true
            delegate: Item {
                x: parent.width * 0.01
                width: parent.width
                height: parent.parent.height * 0.1
                Row {
                    anchors.fill: parent
                    spacing: parent.height * 0.01
                    Text {
                        width: parent.width
                        text: result
                        anchors.verticalCenter: parent.verticalCenter
                        elide: Text.ElideRight
                        maximumLineCount: 1
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: sendQuerySearch(result)
                }
            }
            model: ListModel {
                id: suggestListModel
            }
        }
    }
    function sendQuerySuggest() {
        var suggest = searchText.text

        searchField.suggest(suggest)
    }

    function setSuggestResult(query, results) {
        suggestListModel.clear()
        for (var i = 0; i < results.length; ++i) {
            var result = results[i]

            suggestListModel.append({
                                        result: result
                                    })
        }
    }

    function sendQuerySearch(search) {
        suggestListModel.clear()
        searchField.search(search)
    }
}
