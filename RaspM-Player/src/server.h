#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <memory>
#include "messagehandler/messagehandlerfactory.h"

class Message;
class Player;
class Client;
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    ~Server();
    Player& player();
    std::unique_ptr<Message> handle(std::weak_ptr<Client> client, const Message& message);
signals:

public slots:

private:
    std::unique_ptr<Player> m_player;
    std::unique_ptr<MessageHandlerFactory> m_messageHandler;
};

#endif // SERVER_H
