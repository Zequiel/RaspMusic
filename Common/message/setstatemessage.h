#ifndef PLAYPAUSEMESSAGE_H
#define PLAYPAUSEMESSAGE_H

#include "message.h"

class SetStateMessage : public Message
{
public:
    SetStateMessage();
    bool play;
    bool stop;
    float volume;
    bool next;
    bool previous;

    // Message interface
public:
    virtual MessageType getType() const;

protected:
    virtual void deserialize(const QJsonObject &object);
    virtual void serializeImpl(QJsonObject &object) const;
};

#endif // PLAYPAUSEMESSAGE_H
