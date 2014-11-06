#include "addtoplaylistmessage.h"

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
