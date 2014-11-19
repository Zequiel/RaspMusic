#ifndef MESSAGE_H
#define MESSAGE_H
#include "common_global.h"
#include <memory>
#include <QJsonObject>

enum class MessageType {
    ADD_TO_PLAYLIST, EMPTY
};

class COMMONSHARED_EXPORT Message
{
public:
    Message();
    virtual ~Message();
    virtual MessageType getType() const = 0;
    static std::shared_ptr<Message> buildFromJSon(const QJsonObject &object);
    virtual std::unique_ptr<QJsonObject> serialize() const = 0;

protected:
    virtual void deserialize(const QJsonObject &object) = 0;
private:
    static std::shared_ptr<Message> createMessageInstanceFromJsonType(const QJsonObject &object);
};

#endif // MESSAGE_H
