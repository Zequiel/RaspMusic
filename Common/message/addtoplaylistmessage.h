#ifndef ADDTOPLAYLISTMESSAGE_H
#define ADDTOPLAYLISTMESSAGE_H
#include "message.h"
#include "common_global.h"

class COMMONSHARED_EXPORT AddToPlaylistMessage: public Message
{
public:
    AddToPlaylistMessage();
    const std::vector<std::string>& sources() const;
    void addSource(std::string source);

    // Message interface
public:
    virtual MessageType getType() const override;
    virtual std::unique_ptr<QJsonObject> serialize() const override;
    std::vector<std::string> m_sources;
protected:
    virtual void deserialize(const QJsonObject &object);
};

#endif // ADDTOPLAYLISTMESSAGE_H
