#ifndef ADDTOPLAYLISTMESSAGE_H
#define ADDTOPLAYLISTMESSAGE_H
#include "message.h"

class AddToPlaylistMessage: public Message
{
public:
    AddToPlaylistMessage();
    const std::vector<std::string>& sources() const;

    // Message interface
public:
    virtual MessageType getType() const override;
    virtual std::unique_ptr<QJsonObject> serialize() const override;
    std::vector<std::string> m_sources;
};

#endif // ADDTOPLAYLISTMESSAGE_H
