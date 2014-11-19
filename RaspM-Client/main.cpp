#include <QApplication>
#include <QQmlApplicationEngine>
#include "server.h"

int main(int argc, char *argv[])
{
    ServerDefinition definition = {
        QHostAddress("127.0.0.1"),
        6423,
        "Default server"
    };
    Server server(definition);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
