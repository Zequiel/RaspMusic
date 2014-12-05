import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.2

Window {
    visible: true
    id :main
    width: 200
    height: 350
    //fillHeight: true
    //fillWidth: true

    Rectangle{
        id: logoConnexion
        width: main.width * 0.8
        height: main.height * 0.3
        color: "#CCC"
        x: (main.width - logoConnexion.width) / 2
        y: logoConnexion.x
    }

    Text{
        id: nomConnexion
        text: "Rasp Music"
        font.pointSize: main.width / 10
        x: (main.width - nomConnexion.width) / 2
        y: logoConnexion.y + logoConnexion.height + main.height / 20
    }

    TextField{
        id: loginConnexion
        placeholderText: "Identifiant"
        width: nomConnexion.width
        height: main.height * 0.05
        x: (main.width - loginConnexion.width) / 2
        y: nomConnexion.y + nomConnexion.height + main.height / 20
    }

    TextField{
        id: mdpConnexion
        placeholderText: "Mot de passe"
        width: loginConnexion.width
        height: main.height * 0.05
        x: (main.width - mdpConnexion.width) / 2
        y: loginConnexion.y + loginConnexion.height + main.height / 40
    }

    Button{
        id: inscriptionConnexion
        text: "S'inscrire"
        width: nomConnexion.width / 2 - main.width / 40
        height: loginConnexion.height
        x: loginConnexion.x
        y: mdpConnexion.y + mdpConnexion.height + main.height / 40
    }

    Button{
        id: connexionConnexion
        text: "Connexion"
        width: inscriptionConnexion.width
        height: inscriptionConnexion.height
        x: inscriptionConnexion.x + inscriptionConnexion.width + main.width / 20
        y: inscriptionConnexion.y
    }
}
