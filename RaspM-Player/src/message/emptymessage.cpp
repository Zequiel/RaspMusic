#include "emptymessage.h"

EmptyMessage::EmptyMessage()
{
}

MessageType EmptyMessage::getType() const
{
    return MessageType::EMPTY;
}

std::unique_ptr<QJsonObject> EmptyMessage::serialize() const
{
    return std::unique_ptr<QJsonObject>();
}
