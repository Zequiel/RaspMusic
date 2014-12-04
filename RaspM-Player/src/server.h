#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <memory>
#include "messagehandler/messagehandlerfactory.h"

class Message;
class Player;
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    ~Server();
    Player& player();
    std::unique_ptr<Message> handle(const Message& message);
signals:

public slots:

private:
    std::unique_ptr<Player> m_player;
    MessageHandlerFactory m_messageHandler;
};

#endif // SERVER_H
