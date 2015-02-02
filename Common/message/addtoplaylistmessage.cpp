#include "addtoplaylistmessage.h"
#include <QJsonArray>
#include <iostream>

AddToPlaylistMessage::AddToPlaylistMessage()
{
}

const std::vector<std::string> &AddToPlaylistMessage::sources() const
{
    return m_sources;
}

void AddToPlaylistMessage::addSource(std::string source)
{
    m_sources.push_back(source);
}

MessageType AddToPlaylistMessage::getType() const
{
    return MessageType::ADD_TO_PLAYLIST;
}

void AddToPlaylistMessage::serializeImpl(QJsonObject &object) const
{
    QJsonArray sources;
    for(auto source : m_sources)
    {
        sources.append(QJsonValue(QString::fromStdString(source)));
    }
    object["sources"] = sources;
}

void AddToPlaylistMessage::deserialize(const QJsonObject &object)
{
    QJsonArray sources = object["sources"].toArray();
    for(QJsonValue source: sources)
    {
        m_sources.push_back(source.toString().toStdString());
    }
}
