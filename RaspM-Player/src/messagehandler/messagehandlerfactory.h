#ifndef MESSAGEHANDLERFACTORY_H
#define MESSAGEHANDLERFACTORY_H
#include <memory>
#include <vector>

class MessageHandler;
class Message;
class Server;
class MessageHandlerFactory
{
public:
    MessageHandlerFactory(Server &server);
    ~MessageHandlerFactory();
    const MessageHandler & getHandlerFor(const Message &message) const;
private:
    std::vector<std::unique_ptr<MessageHandler>> m_handlers;
};

#endif // MESSAGEHANDLERFACTORY_H
