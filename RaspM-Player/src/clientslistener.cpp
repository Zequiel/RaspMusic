#include "clientslistener.h"
#include "client.h"
#include "server.h"
#include <easylogging++.h>

ClientsListener::ClientsListener(Server &server): m_tcpServer(this), m_server(server)
{
    quint16 const port = 6423;
    m_newClientConnection = this->connect(&m_tcpServer, &QTcpServer::newConnection, this, &ClientsListener::newClient);
    m_tcpServer.listen(QHostAddress::Any, port);
    LOG(INFO) << "Start accept connection on port " << port;
}

ClientsListener::~ClientsListener()
{
    this->disconnect(m_newClientConnection);
}

void ClientsListener::newClient()
{
    QTcpSocket *socket = m_tcpServer.nextPendingConnection();
    LOG(INFO) << "New client connected";
    std::unique_ptr<Client> client(new Client(*socket, m_server));
    m_clients.push_back(std::move(client));
}
