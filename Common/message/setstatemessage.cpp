#include "setstatemessage.h"

SetStateMessage::SetStateMessage()
{
    play = true;
    stop = false;
    next = false;
    previous = false;
    volume = 1.f;
}

MessageType SetStateMessage::getType() const
{
    return MessageType::STATE;
}

void SetStateMessage::deserialize(const QJsonObject &object)
{
    volume = object["volume"].toDouble();
    play= object["play"].toBool();
    next =object["next"].toBool();
    previous = object["previous"].toBool();
    stop = object["stop"].toBool();
}

void SetStateMessage::serializeImpl(QJsonObject &object) const
{
    object["volume"] = volume;
    object["play"] = play;
    object["next"] = next;
    object["previous"] = previous;
    object["stop"] = stop;
}
