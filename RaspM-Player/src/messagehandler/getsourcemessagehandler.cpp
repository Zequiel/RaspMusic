#include "getsourcemessagehandler.h"
#include <message/message.h>
#include <message/currentsourcemessage.h>
#include "../player.h"

GetSourceMessageHandler::GetSourceMessageHandler(Player &player): MessageHandler(player)
{
}

bool GetSourceMessageHandler::canHandle(const Message &message) const
{
    return message.getType() == MessageType::GET_CURRENT_SOURCE;
}

std::unique_ptr<Message> GetSourceMessageHandler::handle(std::weak_ptr<Client> client, const Message &message)
{
    std::unique_ptr<CurrentSourceMessage> sourceMessage(new CurrentSourceMessage());
    sourceMessage->setSource(m_player.getCurrentSource());
    return std::move(sourceMessage);
}
