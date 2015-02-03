#ifndef CURRENTSOURCEMESSAGE_H
#define CURRENTSOURCEMESSAGE_H
#include "message.h"

class CurrentSourceMessage : public Message
{
public:
    CurrentSourceMessage();
    QString source() const;
    void setSource(const QString &source);

private:
    QString m_source;

    // Message interface
public:
    virtual MessageType getType() const;

protected:
    virtual void deserialize(const QJsonObject &object);
    virtual void serializeImpl(QJsonObject &object) const;
};

#endif // CURRENTSOURCEMESSAGE_H
