#include "messagereaderwriter.h"
#include "message/message.h"
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>

MessageReaderWriter::MessageReaderWriter(QTcpSocket &device, QObject *parent) :
    QObject(parent), m_device(device), m_isReceivingData(false)
{
    m_readDataConnection = QObject::connect(&device, SIGNAL(readyRead()), this, SLOT(readData()));
}

MessageReaderWriter::~MessageReaderWriter()
{
    this->disconnect(m_readDataConnection);
}

void MessageReaderWriter::readData()
{
    while(m_device.bytesAvailable() > 0)
    {
        if(m_isReceivingData)
        {
            handleReadData();
        }
        else
        {
            handleReadDataSize();
        }
    }
}

void MessageReaderWriter::handleBufferReady()
{
    QJsonDocument document = QJsonDocument::fromBinaryData(m_buffer);
    QJsonObject object = document.object();
    auto message = Message::buildFromJSon(object);
    emit messageReceived(message);
}

void MessageReaderWriter::handleReadDataSize()
{
    if(m_device.bytesAvailable() > sizeof(qint32))
    {
        QDataStream out(&m_device);
        out >> m_dataSize;
        m_buffer.clear();
        m_isReceivingData = true;
    }
}

void MessageReaderWriter::handleReadData()
{
    if(m_device.bytesAvailable() >= m_dataSize)
    {
        m_buffer.append(m_device.read(m_dataSize));
        m_isReceivingData = false;
        handleBufferReady();
        m_buffer.clear();
    }
}

void MessageReaderWriter::sendMessage(const Message &message)
{
    auto object = message.serialize();
    QJsonDocument doc(*object);
    QByteArray docSerialized = doc.toBinaryData();
    QDataStream in(&m_device);
    in << (qint32) docSerialized.size();
    m_device.write(docSerialized);
}
