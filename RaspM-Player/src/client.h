#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
#include <messagereaderwriter.h>

class Server;
class Client: public QObject
{
    Q_OBJECT
public:
    Client(QTcpSocket &socket, Server &server);

public slots:
    void handleMessageReceived(std::shared_ptr<Message> message);
private:
    QTcpSocket &m_socket;
    Server &m_server;
    MessageReaderWriter m_readWrite;
};

#endif // CLIENT_H
