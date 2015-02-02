#include <QJsonObject>
#include "message.h"
#include "addtoplaylistmessage.h"
#include "setstatemessage.h"
#include "emptymessage.h"
#include <iostream>

Message::Message()
{
}

Message::~Message()
{

}

std::shared_ptr<Message> Message::createMessageInstanceFromJsonType(const QJsonObject &object)
{
    std::shared_ptr<Message> message;
    MessageType type = (MessageType) object["_type"].toInt();
    switch(type)
    {
    case MessageType::ADD_TO_PLAYLIST:
        message.reset(new AddToPlaylistMessage());
        break;
    case MessageType::STATE:
        message.reset(new SetStateMessage());
        break;
    case MessageType::EMPTY:
    defaults:
        message.reset(new EmptyMessage());
    }

    return message;
}

std::shared_ptr<Message> Message::buildFromJSon(const QJsonObject &object)
{
    std::shared_ptr<Message> message = createMessageInstanceFromJsonType(object);
    if(message)
    {
        message->deserialize(object);
    }
    return message;
}

std::unique_ptr<QJsonObject> Message::serialize() const
{
    std::unique_ptr<QJsonObject> object(new QJsonObject());
    this->serializeImpl(*object);
    (*object)["_type"] = (int) this->getType();
    return object;
}
