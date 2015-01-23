import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
    anchors.verticalCenter: parent.verticalCenter
    width: 135
    height: 20
    Rectangle {
        id: searchField
        objectName: "searchField"
        width: 135
        height: 20
        anchors.left: parent.left
        anchors.leftMargin: 7
        signal suggest(string query)
        signal search(string query)
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
            onTextChanged: sendQuerySuggest()
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

        ListView {
            width: 110
            height: 160
            x: searchField.x
            anchors.top: searchField.bottom
            anchors.topMargin: 20
            visible: suggestListModel.count > 0
            snapMode: ListView.SnapToItem
            focus: true
            delegate: Item {
                x: 5
                width: 80
                height: 20
                Row {
                    spacing: 10
                    Text {
                        text: result
                        anchors.verticalCenter: parent.verticalCenter
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

        Connections {
            target: client
            onSuggestResultReady: setSuggestResult(query, results)
            onSearchResultReady: setSearchResult(query, results)
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
        console.log(search)
        suggestListModel.clear()
        searchField.search(search)
    }

    function setSearchResult(query, results) {
        console.log(JSON.stringify(arguments));
        for (var i = 0; i < results.length; ++i) {
            var result = results[i]
            console.log(result)
            musicListModel.append({
                                    image: result.thumb,
                                    name: result.title,
                                    link: result.url
                                  })
        }
    }
}
