import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
    id: player
    objectName: "player"
    width: parent.width
    height: parent.height * 0.08
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0
    property MusicList musicList: null
    signal sendMusic(string title, string thumb, string link)
    signal sendPlay
    signal sendPause
    signal sendNext
    signal sendPrevious
    signal sendVolume(bool up)

    Image {
        id: musicPicture
        width: parent.height
        height: parent.height
        opacity: 0.3
        anchors.left: parent.left
        anchors.leftMargin: 0
        verticalAlignment: Image.AlignVCenter
        source: "icons/noPicture.png"
    }

    Text {
        id: musicTitle
        width: parent.width - (musicPicture.width + nextButton.width
                               + preventButton.width + playButton.width)
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: musicPicture.width + (parent.width * 0.01)
        verticalAlignment: Text.AlignVCenter
        text: "-"
        font.pixelSize: parent.height * 0.4
        elide: Text.ElideRight
        maximumLineCount: 1
    }

    Button {
        id: nextButton
        width: parent.height
        height: parent.height
        anchors.right: parent.right
        anchors.rightMargin: 0
        style: ButtonStyle {
            background: Image {
                source: "icons/next.png"
            }
        }
        onClicked: player.sendNext()
    }
    Button {
        id: playButton
        width: parent.height
        height: parent.height
        anchors.right: parent.right
        anchors.rightMargin: nextButton.width
        style: ButtonStyle {
            background: Image {
                source: "icons/play.png"
            }
        }
        onClicked: playMusic()
    }
    Button {
        id: pauseButton
        visible: false
        width: parent.height
        height: parent.height
        anchors.right: parent.right
        anchors.rightMargin: nextButton.width
        style: ButtonStyle {
            background: Image {
                source: "icons/pause.png"
            }
        }
        onClicked: pauseMusic()
    }
    Button {
        id: preventButton
        width: parent.height
        height: parent.height
        anchors.right: parent.right
        anchors.rightMargin: nextButton.width + playButton.width
        style: ButtonStyle {
            background: Image {
                source: "icons/prevent.png"
            }
        }
        onClicked: player.sendPrevious()
    }

    Connections {
        target: musicList
        onAddMusic: sendQueryToReadMusic(title, thumb, link)
    }

    Connections {
        target: app
        onChangeMusicData: changeMusicData(title, thumb, url)
    }

    function playMusic() {
        sendPlay()
        changePlayOrPauseVisibility()
    }

    function pauseMusic() {
        sendPause()
        changePlayOrPauseVisibility()
    }

    function changePlayOrPauseVisibility() {
        playButton.visible = !playButton.visible
        pauseButton.visible = !pauseButton.visible
    }

    function sendQueryToReadMusic(title, thumb, link) {
        sendMusic(title, thumb, link)

        if (playButton.visible) {
            changePlayOrPauseVisibility()
            musicTitle.text = title
            musicPicture.source = thumb
            musicPicture.opacity = 1
        }
    }

    function changeMusicData(title, thumb, url) {
        musicTitle.text = title
        musicPicture.source = thumb
    }
}
