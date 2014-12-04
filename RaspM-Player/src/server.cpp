#include "server.h"
#include <message/emptymessage.h>
#include "messagehandler/messagehandler.h"
#include "player.h"
#include <QSettings>

Server::Server(QObject *parent) :
    QObject(parent), m_messageHandler(*this)
{
    QSettings settings("RaspMusic", "Player");
    m_player = std::unique_ptr<Player>(new Player(settings.value("data_cache", "/tmp").toString().toStdString()));
}

Player &Server::player()
{
    return *m_player;
}

Server::~Server()
{

}

std::unique_ptr<Message> Server::handle(const Message &message)
{
    try {
        const MessageHandler &handler = m_messageHandler.getHandlerFor(message);
        return handler.handle(message);
    } catch(std::exception &e) {
        return std::unique_ptr<Message>(new EmptyMessage());
    }
}
