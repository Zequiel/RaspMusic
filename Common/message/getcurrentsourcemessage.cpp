#include "getcurrentsourcemessage.h"

GetCurrentSourceMessage::GetCurrentSourceMessage()
{
}

MessageType GetCurrentSourceMessage::getType() const
{
    return MessageType::GET_CURRENT_SOURCE;
}

void GetCurrentSourceMessage::deserialize(const QJsonObject &object)
{
}

void GetCurrentSourceMessage::serializeImpl(QJsonObject &object) const
{
}

