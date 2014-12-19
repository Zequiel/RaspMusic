#include "server.h"
#include <message/emptymessage.h>
#include "messagehandler/messagehandler.h"
#include "player.h"
#include <QSettings>
#include <QStandardPaths>
#include "serverpresencenotifier.h"

Server::Server(QObject *parent) :
    QObject(parent)
{
    QSettings settings;
    QString defaultCachePath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    std::string cachePath = settings.value("cachePath", defaultCachePath).toString().toStdString();
    m_player = std::unique_ptr<Player>(new Player(cachePath));
    m_messageHandler = std::unique_ptr<MessageHandlerFactory>(new MessageHandlerFactory(*this));
    m_notifier = std::unique_ptr<ServerPresenceNotifier>(new ServerPresenceNotifier());
}

Player &Server::player()
{
    return *m_player;
}

Server::~Server()
{
}

std::unique_ptr<Message> Server::handle(std::weak_ptr<Client> client, const Message &message)
{
    try
    {
        MessageHandler &handler = m_messageHandler->getHandlerFor(message);
        return handler.handle(client, message);
    }
    catch(std::exception &e)
    {
        return std::unique_ptr<Message>(new EmptyMessage());
    }
}
