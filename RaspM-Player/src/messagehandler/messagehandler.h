#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H
#include <memory>
#include <QObject>

class Player;
class Message;
class Client;
class MessageHandler: public QObject
{
    Q_OBJECT
public:
    MessageHandler(Player &player);
    virtual ~MessageHandler();
    virtual bool canHandle(const Message &message) const = 0;
    virtual std::unique_ptr<Message> handle(std::weak_ptr<Client> client, const Message &message) = 0;
protected:
    Player &m_player;
};

#endif // MESSAGEHANDLER_H
