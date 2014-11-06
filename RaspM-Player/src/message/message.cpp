#include <QJsonObject>
#include "message.h"
#include "addtoplaylistmessage.h"

Message::Message()
{
}

std::unique_ptr<Message> Message::createMessageInstanceFromJsonType(const QJsonObject &object)
{
    std::unique_ptr<Message> message;
    QString type = object["type"].toString();
    if(type.toLower() == "add_to_playlist")
    {
        message.reset(new AddToPlaylistMessage());
    }

    return message;
}

std::unique_ptr<Message> Message::buildFromJSon(const QJsonObject &object)
{
    std::unique_ptr<Message> message = createMessageInstanceFromJsonType(object);
    if(message)
    {
        message->deserialize(object);
    }
    return message;
}
