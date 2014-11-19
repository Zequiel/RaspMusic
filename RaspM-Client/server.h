#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>

#include <message/message.h>

#include <QHostAddress>
#include <QTcpSocket>

struct ServerDefinition
{
    QHostAddress address;
    quint16 port;
    std::string name;
};

class Server
{
public:
    Server(const ServerDefinition &connectTo);
    ~Server();
    std::unique_ptr<Message> sendMessage(const Message& message);

private:
    Server();
    QTcpSocket m_socket;
};

#endif // SERVER_H
