#include "player.h"
#include <iostream>
#include <QMediaPlaylist>
#include <QUrl>

Player::Player(const std::string &cacheFolder): m_mediaCollection(cacheFolder)
{
    player.setPlaylist(new QMediaPlaylist());
    player.play();
    connect(this, &Player::addSource, this, &Player::addSourceImpl);
    moveToThread(&m_thread);
    m_thread.start();
}

Player::~Player()
{
}

void Player::addSourceImpl(AddToPlaylistRequest request)
{
    std::string mediaUrl = m_mediaCollection.getMediaFilePath(request.url);
    player.playlist()->addMedia(QUrl(QString::fromStdString("file://"+mediaUrl)));
    player.play();
}
