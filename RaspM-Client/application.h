#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <memory>
#include <message/setstatemessage.h>

class Server;
class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = 0);
    ~Application();

signals:
    void receiveMusicUrl(QString url);
    void changeMusicData(QString title, QString thumb, QString url);

public slots:
    void connect();
    void searchMusicData(QString url);
    void sendMusic(QString title, QString thumb, QString url);
    void sendPlay();
    void sendPause();
    void sendNext();
    void sendPrevious();
    void sendVolume(bool up);

private:
    void initStates();
    SetStateMessage stateMessage;
    QJsonObject serverMusicList;
    std::unique_ptr<Server> m_server;
    QQmlApplicationEngine engine;
};

#endif // APPLICATION_H
