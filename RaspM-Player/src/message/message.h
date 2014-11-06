#ifndef MESSAGE_H
#define MESSAGE_H
#include <memory>
#include <QJsonObject>

enum class MessageType {
    ADD_TO_PLAYLIST, EMPTY
};

class Message
{
public:
    Message();
    virtual MessageType getType() const = 0;
    static std::unique_ptr<Message> buildFromJSon(const QJsonObject &object);
    virtual std::unique_ptr<QJsonObject> serialize() const = 0;

protected:
    virtual void deserialize(const QJsonObject &object) = 0;
private:
    static std::unique_ptr<Message> createMessageInstanceFromJsonType(const QJsonObject &object);
};

#endif // MESSAGE_H
