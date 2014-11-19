#include "server.h"
#include <iostream>
#include <QJsonDocument>
#include <message/addtoplaylistmessage.h>

Server::Server(const ServerDefinition &connectTo): m_socket(this), m_readWrite(m_socket)
{
    m_connected = false;
    QObject::connect(&m_readWrite, &MessageReaderWriter::messageReceived, this, &Server::messageReceived);
    QObject::connect(&m_socket, &QTcpSocket::connected, this, &Server::connected);
    m_socket.connectToHost(connectTo.address, connectTo.port);
}

Server::~Server()
{
    m_socket.disconnectFromHost();
}

void Server::sendMessage(const Message &message)
{
    m_readWrite.sendMessage(message);
}
