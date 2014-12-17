#ifndef SETSTATEHANDLER_H
#define SETSTATEHANDLER_H
#include "messagehandler.h"

class SetStateHandler: public MessageHandler
{
public:
    SetStateHandler(Player &player);

    // MessageHandler interface
public:
    virtual bool canHandle(const Message &message) const;
    virtual std::unique_ptr<Message> handle(std::weak_ptr<Client> client, const Message &message);
};

#endif // SETSTATEHANDLER_H
