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
    const SetStateMessage &state = dynamic_cast<const SetStateMessage&>(message);
    if(state.play) {
        m_player.play();
    }else {
        m_player.pause();
    }
    if(state.next) {
        m_player.next();
    } else if(state.previous) {
        m_player.previous();
    }
    if(state.stop) {
        m_player.stop();
    }
    m_player.setVolume(state.volume);
    return std::unique_ptr<Message>(new EmptyMessage());
}
