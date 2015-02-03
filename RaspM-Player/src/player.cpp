#include "player.h"
#include <iostream>
#include <QMediaPlaylist>
#include <QUrl>
#include <easylogging++.h>

Player::Player(const std::string &cacheFolder): m_mediaCollection(cacheFolder)
{
    player.setPlaylist(new QMediaPlaylist());
    player.play();
    connect(this, &Player::addSource, this, &Player::addSourceImpl);
    connect(this, &Player::stop, &m_thread, &QThread::quit);
    moveToThread(&m_thread);
    m_mediaCollection.moveToThread(&m_thread);
    m_thread.start();
}

Player::~Player()
{
    emit stop();
    m_thread.wait();
}

void Player::addSourceImpl(AddToPlaylistRequest request)
{
    LOG(INFO) << "Add " << request.url;
    std::string mediaUrl = m_mediaCollection.getMediaFilePath(request.url);
    player.playlist()->addMedia(QUrl(QString::fromStdString("file://"+mediaUrl)));
    player.play();
}

void Player::next()
{
    player.playlist()->next();
}

void Player::previous()
{
    player.playlist()->previous();
}

void Player::play()
{
    player.play();
}

void Player::pause()
{
    player.pause();
}

void Player::setVolume(float volume)
{
    player.setVolume(100 * volume);
}

QString Player::getCurrentSource() const
{
   QString source = player.currentMedia().canonicalUrl().toLocalFile();
   return QString::fromStdString(this->m_mediaCollection.getOriginalUrl(source.toStdString()));
}
