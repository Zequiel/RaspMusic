#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
#include <memory>
#include <messagereaderwriter.h>

class Server;
class Client: public QObject
{
    Q_OBJECT
private:
    Client(std::unique_ptr<QTcpSocket> socket, Server &server);

public:
    ~Client();

public:
    static std::shared_ptr<Client> instance(std::unique_ptr<QTcpSocket> socket, Server &server);

public slots:
    void handleMessageReceived(std::shared_ptr<Message> message);

signals:
    void clientLeft();

private:
    std::weak_ptr<Client> m_self;
    std::unique_ptr<QTcpSocket> m_socket;
    Server &m_server;
    MessageReaderWriter m_readWrite;
};

#endif // CLIENT_H
