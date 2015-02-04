import QtQuick 2.0

ListView {
    id: musicList
    objectName: "musicList"
    property string state: "SEARCH"
    signal addMusic(string title, string thumb, string link)
    anchors.top: parent.top
    anchors.topMargin: parent.height * 0.08
    z:-1
    width: parent.width
    height: parent.height * 0.84
    snapMode: ListView.SnapToItem
    highlight: Rectangle {
        color: "grey"
    }
    highlightMoveDuration: 500
    delegate: Item {
        width: musicList.width
        height: musicList.height * 0.1
        Row {
            width: parent.width
            height: parent.height
            spacing: parent.width * 0.01
            Image {
                source: image
                width: parent.height
                height: parent.height
            }

            Text {
                text: title
                font.pixelSize: parent.height * 0.4
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (musicList.state === "SEARCH") {
                    musicList.currentIndex = index;

                    serverMusicList.append({
                                      image: image,
                                      title: title,
                                      link: link
                                  })

                    musicList.addMusic(title, image, link);
                }
            }
        }
    }
    model: (musicList.state === "SEARCH") ? musicListModel: serverMusicList

    Connections {
        target: client
        onSearchResultReady: setSearchResult(query, results)
    }

    ListModel {
        id: musicListModel
    }

    ListModel {
        id: serverMusicList
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

    function changeContent(state){
        musicList.state = state;
    }

}
