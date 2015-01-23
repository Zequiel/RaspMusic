import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    width: 200
    height: 200
    visible: true
    signal connect()
    onBeforeRendering: serverConnection()
    HeaderComponent {
        states: [
            {
                HISTORY: {
                    name: qsTr('Historique'),
                    source: 'icons/history.png',
                    isDefault: true
                }
            }, {
                PLAYLIST: {
                    name: qsTr('Playlist'),
                    source: 'icons/playlist.png'
                }
            }, {
                FAV: {
                    name: qsTr('Favoris'),
                    source: 'icons/star.png'
                }
            }
        ]
    }

    MusicList {}

    PlayerComponent {}

    function serverConnection() {
        this.connect();
    }
}
