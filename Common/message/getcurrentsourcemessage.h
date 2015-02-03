#ifndef GETMESSAGE_H
#define GETMESSAGE_H
#include "message.h"

class GetCurrentSourceMessage: public Message
{
public:
    GetCurrentSourceMessage();

    // Message interface
public:
    virtual MessageType getType() const;

protected:
    virtual void deserialize(const QJsonObject &object);
    virtual void serializeImpl(QJsonObject &object) const;
};

#endif // GETMESSAGE_H
