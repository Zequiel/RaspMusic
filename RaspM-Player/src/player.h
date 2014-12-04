#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QMediaPlayer>
#include "mediacollection.h"

class Player: public QMediaPlayer
{
    Q_OBJECT
public:
    explicit Player(const std::string &cacheFolder);
    virtual ~Player();
private:
public slots:
    void addSource(const std::string &source);
private:
    MediaCollection m_mediaCollection;
};

#endif // PLAYER_H
