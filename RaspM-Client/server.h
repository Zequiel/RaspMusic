#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>

#include <message/message.h>
#include <messagereaderwriter.h>

#include <QHostAddress>
#include <QTcpSocket>

struct ServerDefinition
{
    QHostAddress address;
    quint16 port;
    std::string name;
};

class Server: public QObject
{
    Q_OBJECT
public:
    Server(const ServerDefinition &connectTo);
    ~Server();
    void sendMessage(const Message& message);

public slots:
    void connectedSendMessage();

private slots:
    void connected();

signals:
    void messageReceived(std::shared_ptr<Message> message);
    //void connected();

private:
    Server();
    QTcpSocket m_socket;
    MessageReaderWriter m_readWrite;
};

#endif // SERVER_H
