#include <QJsonObject>
#include "message.h"
#include "addtoplaylistmessage.h"

Message::Message()
{
}

Message::~Message()
{

}

std::shared_ptr<Message> Message::createMessageInstanceFromJsonType(const QJsonObject &object)
{
    std::shared_ptr<Message> message;
    QString type = object["type"].toString();
    if(type.toLower() == "add_to_playlist")
    {
        message.reset(new AddToPlaylistMessage());
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
