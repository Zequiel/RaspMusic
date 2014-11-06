#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H
#include <memory>

class Player;
class Message;
class MessageHandler
{
public:
    MessageHandler(Player &player);
    virtual ~MessageHandler();
    virtual bool canHandle(const Message &message) const = 0;
    virtual std::unique_ptr<Message> handle(const Message &message) const = 0;
protected:
    Player &m_player;
};

#endif // MESSAGEHANDLER_H
