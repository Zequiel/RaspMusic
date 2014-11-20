#include "client.h"
#include "server.h"
#include <QJsonDocument>
#include "message/message.h"
#include <easylogging++.h>

Client::Client(std::unique_ptr<QTcpSocket> socket, Server &server):
    m_socket(std::move(socket)),
    m_server(server),
    m_readWrite(*m_socket)
{
    QObject::connect(&m_readWrite, &MessageReaderWriter::messageReceived, this, &Client::handleMessageReceived);
    QObject::connect(m_socket.get(), &QTcpSocket::disconnected, this, &Client::clientLeft);
}

Client::~Client()
{
    LOG(INFO) << "Client left";
}

void Client::handleMessageReceived(std::shared_ptr<Message> message)
{
    m_server.handle(*message);
}
