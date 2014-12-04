#ifndef ADDTOPLAYLISTHANDLER_H
#define ADDTOPLAYLISTHANDLER_H
#include "common_global.h"
#include "messagehandler.h"

#include <src/requests/addtoplaylistrequest.h>

class AddToPlaylistHandler: public MessageHandler
{
    Q_OBJECT
public:
    AddToPlaylistHandler(Player &player);
    ~AddToPlaylistHandler();

signals:
    void addSource(AddToPlaylistRequest request);

    // MessageHandler interface
public:
    virtual bool canHandle(const Message &message) const override;
    virtual std::unique_ptr<Message> handle(std::weak_ptr<Client> client, const Message &message) override;
};

#endif // ADDTOPLAYLISTHANDLER_H
