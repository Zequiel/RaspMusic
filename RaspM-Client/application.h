#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QJsonObject>
#include <QQmlApplicationEngine>
#include <memory>

class Server;
class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = 0);
    ~Application();

signals:

public slots:
    void connect();
    void sendMusic(QString url);
    void sendStateMessage(QString state);

private:
    void initStates();
    QJsonObject states;
    std::unique_ptr<Server> m_server;
    QQmlApplicationEngine engine;
};

#endif // APPLICATION_H
