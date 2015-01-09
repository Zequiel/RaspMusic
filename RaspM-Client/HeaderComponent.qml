import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle {
    id: content
    anchors.fill: parent
    property variant states
    signal stateChanged(string stateName)

    Button {
        id: contentChoice
        x: 0
        width: 32
        height: 32
        text: qsTr("")
        anchors.right: parent.right
        anchors.rightMargin: 0
        checkable: true
        anchors.top: parent.top
        anchors.topMargin: 0
        iconSource: "icons/menu.png"

        Rectangle {
            x: 0
            width: 100
            height: 96
            color: "#b5b3b3"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.topMargin: parent.height
            anchors.top: parent.top
            z: -1
            visible: parent.checked

            ColumnLayout {
                id: buttons
                anchors.fill: parent
                spacing: 0
            }
        }
    }

    Image {
        id: stateIcon
        x: 0
        y: 0
        width: 32
        height: 32

        Text {
            id: stateName
            x: 32
            width: 61
            height: 32
            text: qsTr("Historique")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 12
        }
    }

    Component.onCompleted: {
        var component = Qt.createComponent('MenuButton.qml');
        var defaultId = 0;
        for(var i=0; i < states.length; ++i) {
            var key = Object.keys(states[i])[0];
            var state = states[i][key];
            if(state.isDefault === true) {
                defaultId = i;
            }

            var object = component.createObject(buttons, {
                                       content: state.name,
                                       image: state.source,
                                       Layout: {
                                           fillWidth: true,
                                           fillHeight: true
                                       }
                                   });
            object.clicked.connect((function() {
                var stateIndex = i;
                return function() {
                    setCurrentState(stateIndex);
                }
            })());
        }
        setCurrentState(defaultId);
    }

    function setCurrentState(index) {
        contentChoice.checked = false
        var key = Object.keys(states[index])[0];
        stateIcon.source = states[index][key].source;
        stateName.text = states[index][key].name;

        stateChanged(key)
    }
}
