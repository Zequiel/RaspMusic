#ifndef EMPTYMESSAGE_H
#define EMPTYMESSAGE_H
#include "message.h"

class EmptyMessage: public Message
{
public:
    EmptyMessage();

    // Message interface
public:
    virtual MessageType getType() const override;
    virtual std::unique_ptr<QJsonObject> serialize() const override;

    // Message interface
protected:
    virtual void deserialize(const QJsonObject &object);
};

#endif // EMPTYMESSAGE_H
