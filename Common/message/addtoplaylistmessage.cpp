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

std::unique_ptr<QJsonObject> AddToPlaylistMessage::serialize() const
{
    std::unique_ptr<QJsonObject> object(new QJsonObject());
    QJsonArray sources;
    for(auto source : m_sources)
    {
        sources.append(QJsonValue(QString::fromStdString(source)));
    }
    (*object)["sources"] = sources;
    (*object)["type"] = QString("add_to_playlist");
    return object;
}

void AddToPlaylistMessage::deserialize(const QJsonObject &object)
{
    std::cout << "add message" << std::endl;
    QJsonArray sources = object["sources"].toArray();
    for(QJsonValue source: sources)
    {
        m_sources.push_back(source.toString().toStdString());
    }
}
