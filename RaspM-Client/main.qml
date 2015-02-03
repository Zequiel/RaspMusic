import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: mainLayout
    width: Screen.width
    height: Screen.height
    minimumWidth: 200
    minimumHeight: 200
    visible: true

    HeaderComponent {
        id: header
        menus: [
            {
                    title: qsTr('Search'),
                    image: 'icons/search.png',
                    state: "SEARCH"
            }, {
                    title: qsTr('History'),
                    image: 'icons/history.png',
                    state: "HISTORY"
            }
        ]
    }

    MusicList {
        id: musicList
        Component.onCompleted: {
            header.stateChanged.connect(musicList.changeContent);
        }
    }

    PlayerComponent {
        musicList: musicList
    }
}
