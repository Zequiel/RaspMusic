#include "setstatehandler.h"
#include <message/setstatemessage.h>
#include <message/emptymessage.h>
#include "../player.h"

SetStateHandler::SetStateHandler(Player &player): MessageHandler(player)
{

}

bool SetStateHandler::canHandle(const Message &message) const
{
    return message.getType() == MessageType::STATE;
}

std::unique_ptr<Message> SetStateHandler::handle(std::weak_ptr<Client> client, const Message &message)
{
    //TODO implémenter
    return std::unique_ptr<Message>(new EmptyMessage());
}
