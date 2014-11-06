#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QMediaPlayer>

class Player: public QMediaPlayer
{
    Q_OBJECT
public:
    explicit Player();
    virtual ~Player();
private:
    QString getMediaUrl(const std::string &source);
public slots:
    void addSource(const std::string &source);
private:
};

#endif // PLAYER_H
