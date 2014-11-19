#include <QApplication>
#include <QQmlApplicationEngine>
#include "server.h"

int main(int argc, char *argv[])
{
    ServerDefinition definition = {
        QHostAddress::LocalHost,
        6423,
        "Default server"
    };
    Server server(definition);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    auto object = engine.rootObjects()[0];
    QObject::connect(object, SIGNAL(clickedSig()), &server, SLOT(connectedSendMessage()));

    return app.exec();
}
