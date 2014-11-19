#include "addtoplaylisthandler.h"
#include <message/addtoplaylistmessage.h>
#include <message/emptymessage.h>
#include "../player.h"

AddToPlaylistHandler::AddToPlaylistHandler(Player &player): MessageHandler(player)
{
}

AddToPlaylistHandler::~AddToPlaylistHandler()
{

}

bool AddToPlaylistHandler::canHandle(const Message &message) const
{
    return message.getType() == MessageType::ADD_TO_PLAYLIST;
}

std::unique_ptr<Message> AddToPlaylistHandler::handle(const Message &genericMessage) const
{
    const AddToPlaylistMessage &message = dynamic_cast<const AddToPlaylistMessage&>(genericMessage);
    for(const auto &source : message.sources())
    {
        m_player.addSource(source);
    }
    return std::unique_ptr<Message>(new EmptyMessage());
}
