#ifndef MESSAGEREADERWRITER_H
#define MESSAGEREADERWRITER_H

#include <QObject>
#include <QTcpSocket>
#include <QMetaObject>
#include <QTimer>
#include <memory>

class Message;
class MessageReaderWriter: public QObject
{
    Q_OBJECT
public:
    explicit MessageReaderWriter(QTcpSocket &ioDevice, QObject *parent = 0);
    ~MessageReaderWriter();

private slots:
    void readData();
private:
    void handleBufferReady();
    void handleReadDataSize();
    void handleReadData();

signals:
    void messageReceived(std::shared_ptr<Message> message);
public slots:
    void sendMessage(const Message &message);

private:
    QTcpSocket &m_device;
    bool m_isReceivingData;
    qint32 m_dataSize;
    QByteArray m_buffer;
    QMetaObject::Connection m_readDataConnection;
    QTimer timer;

};

#endif // MESSAGEREADERWRITER_H
