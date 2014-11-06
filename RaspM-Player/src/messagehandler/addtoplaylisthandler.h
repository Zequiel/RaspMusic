#ifndef ADDTOPLAYLISTHANDLER_H
#define ADDTOPLAYLISTHANDLER_H
#include "messagehandler.h"

class AddToPlaylistHandler: public MessageHandler
{
public:
    AddToPlaylistHandler(Player &player);
    ~AddToPlaylistHandler();

    // MessageHandler interface
public:
    virtual bool canHandle(const Message &message) const override;
    virtual std::unique_ptr<Message> handle(const Message &message) const override;
};

#endif // ADDTOPLAYLISTHANDLER_H
