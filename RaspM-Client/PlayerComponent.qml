import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    id: player
    objectName: "player"
    width: parent.width
    height: 34
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0
    property MusicList musicList: null
    signal sendMusic(string link)

    Image {
        id: musicPicture
        width: 32
        height: 32
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
        anchors.leftMargin: musicPicture.width
        verticalAlignment: Text.AlignVCenter
        text: "-"
        font.pixelSize: 12
    }

    Button {
        id: nextButton
        width: 32
        height: 32
        anchors.right: parent.right
        anchors.rightMargin: 0
        iconSource: "icons/next.png"
        onClicked: nextMusic()
    }
    Button {
        id: playButton
        width: 32
        height: 32
        anchors.right: parent.right
        anchors.rightMargin: nextButton.width
        iconSource: "icons/play.png"
        onClicked: playMusic()
    }
    Button {
        id: pauseButton
        visible: false
        width: 32
        height: 32
        anchors.right: parent.right
        anchors.rightMargin: nextButton.width
        iconSource: "icons/pause.png"
        onClicked: pauseMusic()
    }
    Button {
        id: preventButton
        width: 32
        height: 32
        anchors.right: parent.right
        anchors.rightMargin: nextButton.width + playButton.width
        iconSource: "icons/prevent.png"
        onClicked: preventMusic()
    }

    Connections {
        target: musicList
        onAddMusic: sendQueryToReadMusic(title, thumb, link)
    }

    function nextMusic() {}

    function playMusic() {
        changePlayOrPauseVisibility()
    }

    function pauseMusic() {
        changePlayOrPauseVisibility()
    }

    function preventMusic() {}

    function changePlayOrPauseVisibility() {
        playButton.visible = !playButton.visible
        pauseButton.visible = !pauseButton.visible
    }

    function sendQueryToReadMusic(title, thumb, link) {

        player.sendMusic(link)

        if (playButton.visible) {
            changePlayOrPauseVisibility()
            musicTitle.text = title
            musicPicture.source = thumb
        }
    }
}
