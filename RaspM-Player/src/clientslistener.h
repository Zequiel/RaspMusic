#ifndef CLIENTSLISTENER_H
#define CLIENTSLISTENER_H
#include <QObject>
#include <QTcpServer>
#include <vector>
#include <memory>

class Server;
class Client;
class ClientsListener: public QObject
{
    Q_OBJECT
public:
    ClientsListener(Server &server);
    ~ClientsListener();
public slots:
    void newClient();
private:
    QTcpServer m_tcpServer;
    QMetaObject::Connection m_newClientConnection;
    std::vector<std::unique_ptr<Client>> m_clients;
    Server &m_server;
};

#endif // CLIENTSLISTENER_H
