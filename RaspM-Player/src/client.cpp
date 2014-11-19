#include "client.h"
#include "server.h"
#include <QJsonDocument>
#include "message/message.h"
#include <easylogging++.h>

Client::Client(QTcpSocket &socket, Server &server):
    m_socket(socket),
    m_server(server),
    m_readWrite(socket)
{
    this->connect(&m_readWrite, &MessageReaderWriter::messageReceived, this, &Client::handleMessageReceived);
}

void Client::handleMessageReceived(std::shared_ptr<Message> message)
{
    LOG(INFO) << "Message received";
    m_server.handle(*message);
}
