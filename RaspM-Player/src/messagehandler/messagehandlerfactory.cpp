#include "messagehandlerfactory.h"
#include "addtoplaylisthandler.h"
#include "../server.h"

MessageHandlerFactory::MessageHandlerFactory(Server &server)
{
    m_handlers.push_back(std::unique_ptr<MessageHandler>(new AddToPlaylistHandler(server.player())));
}

MessageHandlerFactory::~MessageHandlerFactory()
{

}

MessageHandler &MessageHandlerFactory::getHandlerFor(const Message &message) const
{
    for(auto &handler : m_handlers)
    {
        if(handler->canHandle(message))
        {
            return *handler;
        }
    }
    throw std::exception();
}
