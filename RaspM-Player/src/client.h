#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>

class Server;
class Client
{
public:
    Client(QTcpSocket &socket, Server &server);

    void handleReadDataSize();
    void handleReadData();
public slots:
    void readData();
private:
    void handleBufferReady();
private:
    QTcpSocket &m_socket;
    Server &m_server;
    bool m_isReceivingData;
    qint32 m_dataSize;
    QByteArray m_buffer;
};

#endif // CLIENT_H
