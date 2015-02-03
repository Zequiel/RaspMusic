#include "currentsourcemessage.h"

CurrentSourceMessage::CurrentSourceMessage()
{
}
QString CurrentSourceMessage::source() const
{
    return m_source;
}

void CurrentSourceMessage::setSource(const QString &source)
{
    m_source = source;
}

MessageType CurrentSourceMessage::getType() const
{
    return MessageType::CURRENT_SOURCE;
}

void CurrentSourceMessage::deserialize(const QJsonObject &object)
{
    m_source = object["source"].toString();
}

void CurrentSourceMessage::serializeImpl(QJsonObject &object) const
{
    object["source"] = m_source;
}

