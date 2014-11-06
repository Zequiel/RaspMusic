#include "message.h"

Message::Message()
{
}

std::unique_ptr<Message> Message::buildFromJSon(const QJsonObject &object)
{
    return std::unique_ptr<Message>();
}
