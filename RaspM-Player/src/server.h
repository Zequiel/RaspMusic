#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <memory>
#include "player.h"
#include "messagehandler/messagehandlerfactory.h"

class Message;
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    Player& player();
    std::unique_ptr<Message> handle(const Message& message);
signals:

public slots:

private:
    Player m_player;
    MessageHandlerFactory m_messageHandler;
};

#endif // SERVER_H
