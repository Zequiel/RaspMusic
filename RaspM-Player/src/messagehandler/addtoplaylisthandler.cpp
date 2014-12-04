#include "addtoplaylisthandler.h"
#include <message/addtoplaylistmessage.h>
#include <message/emptymessage.h>
#include "../player.h"
#include <easylogging++.h>

AddToPlaylistHandler::AddToPlaylistHandler(Player &player): MessageHandler(player)
{
    connect(this, &AddToPlaylistHandler::addSource, &player, &Player::addSource);
}

AddToPlaylistHandler::~AddToPlaylistHandler()
{

}

bool AddToPlaylistHandler::canHandle(const Message &message) const
{
    return message.getType() == MessageType::ADD_TO_PLAYLIST;
}

std::unique_ptr<Message> AddToPlaylistHandler::handle(std::weak_ptr<Client> client, const Message &genericMessage)
{
    const AddToPlaylistMessage &message = dynamic_cast<const AddToPlaylistMessage&>(genericMessage);
    for(const auto &source : message.sources())
    {
        AddToPlaylistRequest request(client, source);
        emit addSource(request);
    }
    return std::unique_ptr<Message>(new EmptyMessage());
}
