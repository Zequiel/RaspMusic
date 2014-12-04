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

std::shared_ptr<Client> Client::instance(std::unique_ptr<QTcpSocket> socket, Server &server)
{
    std::shared_ptr<Client> client(new Client(std::move(socket), server));
    client->m_self = client;
    return client;
}

void Client::handleMessageReceived(std::shared_ptr<Message> message)
{
    m_server.handle(m_self, *message);
}
