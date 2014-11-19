#include "clientslistener.h"
#include "client.h"
#include "server.h"
#include <iostream>

ClientsListener::ClientsListener(Server &server): m_tcpServer(this), m_server(server)
{
    m_newClientConnection = this->connect(&m_tcpServer, &QTcpServer::newConnection, this, &ClientsListener::newClient);
    m_tcpServer.listen(QHostAddress::Any, 6423);
    std::cout << "Accept connection on port " << 6423 << std::endl;
}

ClientsListener::~ClientsListener()
{
    this->disconnect(m_newClientConnection);
}

void ClientsListener::newClient()
{
    std::cout << "New client !" << std::endl;
    QTcpSocket *socket = m_tcpServer.nextPendingConnection();
    std::unique_ptr<Client> client(new Client(*socket, m_server));
    m_clients.push_back(std::move(client));
}
