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
    std::unique_ptr<QTcpSocket> socket(m_tcpServer.nextPendingConnection());
    LOG(INFO) << "New client connected";
    std::unique_ptr<Client> client(new Client(std::move(socket), m_server));
    QObject::connect(client.get(), &Client::clientLeft, this, &ClientsListener::clientLeft);
    m_clients.push_back(std::move(client));
}

void ClientsListener::clientLeft()
{
    Client *client = dynamic_cast<Client*>(sender());
    m_clients.erase(
                std::remove_if(
                    m_clients.begin(),
                    m_clients.end(),
                    [client](std::unique_ptr<Client> &other)
                    {
                        return other.get() == client;
                    }
                ),
            m_clients.end()
            );
}
