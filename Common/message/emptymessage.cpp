#include "emptymessage.h"

EmptyMessage::EmptyMessage()
{
}

MessageType EmptyMessage::getType() const
{
    return MessageType::EMPTY;
}

void EmptyMessage::serializeImpl(QJsonObject &object) const
{

}

void EmptyMessage::deserialize(const QJsonObject &object)
{

}
