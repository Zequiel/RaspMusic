#include "server.h"
#include <message/emptymessage.h>
#include "messagehandler/messagehandler.h"

Server::Server(QObject *parent) :
    QObject(parent), m_player(), m_messageHandler(*this)
{
}

Player &Server::player()
{
    return m_player;
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
