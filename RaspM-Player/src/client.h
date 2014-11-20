#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
#include <memory>
#include <messagereaderwriter.h>

class Server;
class Client: public QObject
{
    Q_OBJECT
public:
    Client(std::unique_ptr<QTcpSocket> socket, Server &server);
    ~Client();

public slots:
    void handleMessageReceived(std::shared_ptr<Message> message);

signals:
    void clientLeft();

private:
    std::unique_ptr<QTcpSocket> m_socket;
    Server &m_server;
    MessageReaderWriter m_readWrite;
};

#endif // CLIENT_H
