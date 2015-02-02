import QtQuick 2.0

ListView {
    id: musicList
    objectName: "musicList"
    signal addMusic(string title, string thumb, string link)
    anchors.top: parent.top
    anchors.topMargin: 34
    z:-1
    width: parent.width
    height: 132
    snapMode: ListView.SnapToItem
    focus: true
    delegate: Item {
        x: 5
        width: 80
        height: 20
        Row {
            spacing: 10
            Image {
                source: image
                width: 20
                height: 20
            }

            Text {
                text: title
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: musicList.addMusic(title, image, link)
        }
    }
    model: ListModel {
        id: musicListModel
    }

    Connections {
        target: client
        onSearchResultReady: setSearchResult(query, results)
    }

    function setSearchResult(query, results) {
        musicListModel.clear();
        for (var i = 0; i < results.length; ++i) {
            var result = results[i]
            musicListModel.append({
                                      image: result.thumb,
                                      title: result.title,
                                      link: result.url
                                  })
        }
    }
}
