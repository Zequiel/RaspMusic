#include "application.h"
#include "server.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>

#include <message/addtoplaylistmessage.h>
#include <message/setstatemessage.h>
#include <providers/youtubesearchclient.h>

Application::Application(QObject *parent) :
    QObject(parent)
{
    this->initStates();

    YoutubeSearchClient* client = new YoutubeSearchClient(this);
    engine.rootContext()->setContextProperty("client", client);
    engine.load(QUrl(QStringLiteral("qrc:/mainLayout.qml")));

    auto mainObject = engine.rootObjects()[0];

    auto searchField = mainObject->findChild<QObject*>("searchField");
    QObject::connect(searchField, SIGNAL(suggest(QString)), client, SLOT(suggest(QString)));
    QObject::connect(searchField, SIGNAL(search(QString)), client, SLOT(search(QString)));

    auto playerComponent = mainObject->findChild<QObject*>("player");
    QObject::connect(playerComponent, SIGNAL(sendMusic(QString)), this, SLOT(sendMusic(QString)));
    QObject::connect(playerComponent, SIGNAL(sendStateMessage(QString)), this, SLOT(sendStateMessage(QString)));

    this->connect();
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
}

void Application::sendMusic(QString url)
{
    AddToPlaylistMessage message;
    message.addSource(url.toStdString());
    m_server->sendMessage(message);
}

void Application::sendStateMessage(QString state)
{
    this->initStates();

    states.insert(state, true);

    SetStateMessage message;
    message.buildFromJSon(states);
    m_server->sendMessage(message);
}

void Application::initStates()
{
    states.insert("play", false);
    states.insert("volume", 1.f);
    states.insert("play", false);
    states.insert("next", false);
    states.insert("previous", false);
    states.insert("stop", false);
}
