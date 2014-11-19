#include "player.h"
#include <iostream>
#include <QMediaPlaylist>
#include <QUrl>
#include <QProcess>

Player::Player()
{
    this->setPlaylist(new QMediaPlaylist());
    this->play();
}

Player::~Player()
{
}

QString Player::getMediaUrl(const std::string &source)
{
    QProcess youtubeDl;
    youtubeDl.setArguments({ "--get-url", source.c_str() });
    youtubeDl.setProgram("youtube-dl");
    youtubeDl.start();
    youtubeDl.waitForFinished();
    QByteArray output = youtubeDl.readAllStandardOutput();

    return output;
}

void Player::addSource(const std::string &source)
{
    QString mediaUrl = getMediaUrl(source);
    this->playlist()->addMedia(QUrl(mediaUrl));
    this->play();
}
