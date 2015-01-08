#include "application.h"
#include "server.h"

#include <QQmlApplicationEngine>
#include <iostream>

#include <message/addtoplaylistmessage.h>

Application::Application(QObject *parent) :
    QObject(parent)
{
    engine.load(QUrl(QStringLiteral("qrc:/mainLayout.qml")));
    /*auto object = engine.rootObjects()[0];
    QObject::connect(object, SIGNAL(connect()), this, SLOT(connect()));*/
    std::cout << "app\n" << std::endl;
}

Application::~Application()
{

}

void Application::connect()
{
    ServerDefinition definition = {
        QHostAddress("127.0.0.1"),
        6423,
        "Default server"
    };
    m_server = std::unique_ptr<Server>(new Server(definition));
    auto object = engine.rootObjects()[0];
    QObject::connect(object, SIGNAL(send(QString)), this, SLOT(sendSource(QString)));
}

void Application::sendSource(QString url)
{
    AddToPlaylistMessage message;
    message.addSource(url.toStdString());
    m_server->sendMessage(message);
}
