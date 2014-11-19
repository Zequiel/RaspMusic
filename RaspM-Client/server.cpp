#include "server.h"
#include <iostream>
#include <QJsonDocument>
#include <message/addtoplaylistmessage.h>

Server::Server(const ServerDefinition &connectTo): m_socket(this), m_readWrite(m_socket)
{
    std::cout << "Connecting to " << connectTo.address.toString().toStdString() << "..." << std::endl;
    this->connect(&m_readWrite, &MessageReaderWriter::messageReceived, this, &Server::messageReceived);
    this->connect(&m_socket, &QTcpSocket::connected, this, &Server::connected);
    m_socket.connectToHost(connectTo.address, connectTo.port);
    m_socket.waitForConnected();
}

Server::~Server()
{
    m_socket.disconnectFromHost();
}

void Server::sendMessage(const Message &message)
{
    m_readWrite.sendMessage(message);
}

void Server::connectedSendMessage()
{
    AddToPlaylistMessage message;
    message.addSource("https://www.youtube.com/watch?v=zSAJ0l4OBHM");
    this->sendMessage(message);
}

void Server::connected()
{
    std::cout << "connected" << std::endl;
}
