#include "messagereaderwriter.h"
#include "message/message.h"
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>

QByteArray intToByteArray(qint32 val);
qint32 byteArrayToInt(QByteArray array);

MessageReaderWriter::MessageReaderWriter(QTcpSocket &device, QObject *parent) :
    QObject(parent), m_device(device), m_isReceivingData(false)
{
    std::cout << "Building new MessageRW" << std::endl;
    m_readDataConnection = QObject::connect(&device, SIGNAL(readyRead()), this, SLOT(readData()));
    this->connect(&m_device, &QTcpSocket::disconnected, [] {
        std::cout << "disconnected" << std::endl;
    });
    QObject::connect(&m_device, &QTcpSocket::bytesWritten, [](quint64 size) {
       std::cout << size << " writen !"  << std::endl;
    });
    QObject::connect(&m_device, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), [this] (QAbstractSocket::SocketError) {
           std::cout<< "ERROR " << this->m_device.errorString().toStdString() << std::endl;
        });
}

MessageReaderWriter::~MessageReaderWriter()
{
    std::cout << "delete reader writer" << std::endl;
    this->disconnect(m_readDataConnection);
}

void MessageReaderWriter::readData()
{
    std::cout << "read" << std::endl;
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
    m_buffer.append(m_device.read(sizeof(qint32) - m_buffer.size()));
    if(m_buffer.size() == sizeof(qint32))
    {
        m_dataSize = byteArrayToInt(m_buffer);
        m_buffer.clear();
        m_isReceivingData = true;
    }
}

void MessageReaderWriter::handleReadData()
{
    m_buffer.append(m_device.read(m_dataSize - m_buffer.size()));
    if(m_buffer.size() == m_dataSize)
    {
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
    QByteArray bufferToSend = intToByteArray(docSerialized.size());
    bufferToSend.append(docSerialized);
    qDebug() << bufferToSend.toBase64().data() << "\n";
    std::cout << "Send " << bufferToSend.size() << " bytes" << std::endl;
    m_device.write(bufferToSend);
}

QByteArray intToByteArray(qint32 val)
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::ReadWrite);
    stream << val;
    return array;
}

qint32 byteArrayToInt(QByteArray array)
{
    QDataStream stream(&array, QIODevice::ReadWrite);
    qint32 val;
    stream >> val;
    return val;
}
