#include "application.h"
#include "server.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>

#include <message/addtoplaylistmessage.h>
#include <message/currentsourcemessage.h>
#include <message/getcurrentsourcemessage.h>
#include <message/setstatemessage.h>
#include <providers/youtubesearchclient.h>

Application::Application(QObject *parent) :
    QObject(parent)
{
    QTimer* timer = new QTimer(this);

    timer->setInterval(1000);

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(getCurrentSource()));

    timer->start();

    this->initStates();

    YoutubeSearchClient* client = new YoutubeSearchClient(this);
    engine.rootContext()->setContextProperty("client", client);
    engine.rootContext()->setContextProperty("app", this);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    auto mainObject = engine.rootObjects()[0];

    auto searchField = mainObject->findChild<QObject*>("searchField");
    QObject::connect(searchField, SIGNAL(suggest(QString)), client, SLOT(suggest(QString)));
    QObject::connect(searchField, SIGNAL(search(QString)), client, SLOT(search(QString)));

    auto playerComponent = mainObject->findChild<QObject*>("player");
    QObject::connect(playerComponent, SIGNAL(sendMusic(QString, QString, QString)), this, SLOT(sendMusic(QString, QString, QString)));
    QObject::connect(playerComponent, SIGNAL(sendPlay()), this, SLOT(sendPlay()));
    QObject::connect(playerComponent, SIGNAL(sendPause()), this, SLOT(sendPause()));
    QObject::connect(playerComponent, SIGNAL(sendNext()), this, SLOT(sendNext()));
    QObject::connect(playerComponent, SIGNAL(sendPrevious()), this, SLOT(sendPrevious()));
    QObject::connect(playerComponent, SIGNAL(sendVolume(bool)), this, SLOT(sendVolume(bool)));

    this->connect();
    QObject::connect(m_server.get(), SIGNAL(messageReceived(std::shared_ptr<Message>)), this, SLOT(searchMusicData(std::shared_ptr<Message>)));
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

void Application::getCurrentSource()
{
    GetCurrentSourceMessage message;
    m_server->sendMessage(message);
}

void Application::searchMusicData(std::shared_ptr<Message> message)
{
    QString url = dynamic_cast<CurrentSourceMessage&>(*message).source();
    std::cout << url.toStdString() << std::endl;
    QJsonObject music = serverMusicList[url].toObject();

    changeMusicData(music["title"].toString(), music["thumb"].toString(), url);
}

void Application::sendMusic(QString title, QString thumb, QString url)
{
    QJsonObject music;
    music["title"] = title;
    music["thumb"] = thumb;

    serverMusicList.insert(url, music);

    AddToPlaylistMessage message;
    message.addSource(url.toStdString());
    m_server->sendMessage(message);
}

void Application::sendPlay()
{
    this->initStates();

    stateMessage.play = true;

    m_server->sendMessage(stateMessage);
}

void Application::sendPause()
{
    this->initStates();

    stateMessage.stop = true;

    m_server->sendMessage(stateMessage);
}

void Application::sendNext()
{
    this->initStates();

    stateMessage.next = true;

    m_server->sendMessage(stateMessage);
}

void Application::sendPrevious()
{
    this->initStates();

    stateMessage.previous = true;

    m_server->sendMessage(stateMessage);
}

void Application::sendVolume(bool up)
{
    this->initStates();

    stateMessage.volume += (up) ? 1.f : -1.f;

    m_server->sendMessage(stateMessage);
}

void Application::initStates()
{
    stateMessage.play = false;
    stateMessage.volume = 1.f;
    stateMessage.play = false;
    stateMessage.next = false;
    stateMessage.previous = false;
    stateMessage.stop = false;
}
