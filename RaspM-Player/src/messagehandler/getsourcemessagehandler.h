#ifndef GETSOURCEMESSAGEHANDLER_H
#define GETSOURCEMESSAGEHANDLER_H
#include "messagehandler.h"

class GetSourceMessageHandler : public MessageHandler
{
public:
    GetSourceMessageHandler(Player &player);

    // MessageHandler interface
public:
    virtual bool canHandle(const Message &message) const override;
    virtual std::unique_ptr<Message> handle(std::weak_ptr<Client> client, const Message &message);
};

#endif // GETSOURCEMESSAGEHANDLER_H
