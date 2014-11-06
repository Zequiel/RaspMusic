#include "client.h"
#include "server.h"
#include <QJsonDocument>
#include "message/message.h"

qint32 byteArrayToInt(QByteArray array);

Client::Client(QTcpSocket &socket, Server &server):
    m_socket(socket),
    m_server(server),
    m_isReceivingData(false)
{
}

void Client::handleReadDataSize()
{
    m_buffer.append(m_socket.read(sizeof(qint32) - m_buffer.size()));
    if(m_buffer.size() == sizeof(qint32))
    {
        m_dataSize = byteArrayToInt(m_buffer);
        m_buffer.clear();
        m_isReceivingData = true;
    }
}

void Client::handleReadData()
{
    m_buffer.append(m_socket.read(m_dataSize - m_buffer.size()));
    if(m_buffer.size() == m_dataSize)
    {
        m_isReceivingData = false;
        handleBufferReady();
        m_buffer.clear();
    }
}

void Client::readData()
{
    while(m_socket.bytesAvailable() > 0)
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

void Client::handleBufferReady()
{
    QJsonDocument document = QJsonDocument::fromBinaryData(m_buffer);
    QJsonObject object = document.object();
    auto message = Message::buildFromJSon(object);
    m_server.handle(*message);
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
