#include "server.h"
#include <message/emptymessage.h>
#include "messagehandler/messagehandler.h"
#include "player.h"
#include <QSettings>
#include <QStandardPaths>

Server::Server(QObject *parent) :
    QObject(parent), m_messageHandler(*this)
{
    QSettings settings;
    QString defaultCachePath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    std::string cachePath = settings.value("cachePath", defaultCachePath).toString().toStdString();
    m_player = std::unique_ptr<Player>(new Player(cachePath));
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
    try
    {
        const MessageHandler &handler = m_messageHandler.getHandlerFor(message);
        return handler.handle(message);
    }
    catch(std::exception &e)
    {
        return std::unique_ptr<Message>(new EmptyMessage());
    }
}
