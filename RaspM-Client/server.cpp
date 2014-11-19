#include "server.h"
#include <iostream>

Server::Server(const ServerDefinition &connectTo)
{
    std::cout << "connect..." << std::endl;
    m_socket.connectToHost(connectTo.address, connectTo.port);
}

Server::~Server()
{
    m_socket.disconnectFromHost();
}


