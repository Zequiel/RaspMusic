#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QMediaPlayer>
#include <QThread>
#include "mediacollection.h"
#include "requests/addtoplaylistrequest.h"

class Player: public QObject
{
    Q_OBJECT
public:
    explicit Player(const std::string &cacheFolder);
    virtual ~Player();

signals:
    void sourceAdded(AddToPlaylistRequest request);

signals:
    void addSource(AddToPlaylistRequest request);
public slots:
    void addSourceImpl(AddToPlaylistRequest request);

private:
    MediaCollection m_mediaCollection;
    QMediaPlayer player;
    QThread m_thread;
};

#endif // PLAYER_H
