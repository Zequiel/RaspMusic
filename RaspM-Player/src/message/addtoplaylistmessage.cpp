#include "addtoplaylistmessage.h"
#include <QJsonArray>

AddToPlaylistMessage::AddToPlaylistMessage()
{
}

const std::vector<std::string> &AddToPlaylistMessage::sources() const
{
    return m_sources;
}

MessageType AddToPlaylistMessage::getType() const
{
    return MessageType::ADD_TO_PLAYLIST;
}

std::unique_ptr<QJsonObject> AddToPlaylistMessage::serialize() const
{
    return std::unique_ptr<QJsonObject>();
}

void AddToPlaylistMessage::deserialize(const QJsonObject &object)
{
    QJsonArray sources = object["sources"].toArray();
    for(QJsonValue source: sources)
    {
        m_sources.push_back(source.toString().toStdString());
    }
}
