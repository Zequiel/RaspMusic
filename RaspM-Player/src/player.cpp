#include "player.h"
#include <iostream>
#include <QMediaPlaylist>
#include <QUrl>

Player::Player()
{
    this->setPlaylist(new QMediaPlaylist());
    this->play();
}

Player::~Player()
{
}

void Player::addSource(const std::string &source)
{
    std::string mediaUrl = m_mediaCollection.getMediaFilePath(source);
    this->playlist()->addMedia(QUrl(QString::fromStdString("file://"+mediaUrl)));
    this->play();
}
