#include "mediacollection.h"
#include <QProcess>
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include <QVariantMap>
#include <QCryptographicHash>
#include <QSqlQuery>
#include <QThread>
#include <easylogging++.h>
#include <QDir>
#include <QFileInfo>

enum MediaStatus {
    DOWNLOADING = 0, DOWNLOADED = 1, INCOMPLETE = 2
};

MediaCollection::MediaCollection(const std::string &cacheFolder): m_cacheFolder(cacheFolder)
{
    load();
    restartIncompleteDownloads();
}

MediaCollection::MediaCollection()
{
    load();
    restartIncompleteDownloads();
}

MediaCollection::~MediaCollection()
{
    QSqlQuery query("UPDATE musics SET status = 2 WHERE status = 0;", m_db);
    query.exec();
}

void MediaCollection::setCacheFolder(const std::string &path)
{
    m_cacheFolder = path;
}

std::string MediaCollection::getMediaFilePath(const std::string &url)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT id, status FROM musics WHERE url = :url");
    query.bindValue(":url", QString::fromStdString(url));
    query.exec();
    if(query.next())
    {
        if(query.value(1).toInt() == DOWNLOADING && m_downloadingIds.count(query.value(0).toInt()) == 0)
        {
            downloadMediaById(query.value(0).toInt());
        }
        return m_cacheFolder + "/" + query.value(0).toString().toStdString();
    }
    std::string path = downloadMedia(url);
    return path;
}

std::string MediaCollection::getOriginalUrl(const std::string path) const
{
    QSqlQuery query(m_db);
    QFileInfo file(QString::fromStdString(path));
    QString id = file.baseName();
    query.prepare("SELECT url FROM musics WHERE id = :id");
    query.bindValue(":id", id.toInt());
    query.exec();
    if(query.next())
    {
        return query.value(0).toString().toStdString();
    }
    return "";
}

void MediaCollection::load()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QString databasePath = QString::fromStdString(m_cacheFolder + "/" +  "data.sqlite");
    m_db.setDatabaseName(databasePath);
    if(!m_db.open())
    {
        LOG(INFO) << "Error while opening database: " << databasePath.toStdString();
    }
    QSqlQuery query("CREATE TABLE IF NOT EXISTS musics(id INTEGER PRIMARY KEY autoincrement, url TEXT UNIQUE, status INT, title TEXT);", m_db);
    if(!query.exec())
    {
        LOG(INFO) << "Error while creating database schemas";
    }
}

std::string MediaCollection::downloadMediaById(int id)
{
    m_downloadingIds.insert(id);
    QSqlQuery query(m_db);
    query.prepare("SELECT url FROM musics WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    if(query.next())
    {
        std::string url = query.value(0).toString().toStdString();
        std::string path = m_cacheFolder + "/" + QString::number(id).toStdString();
        QProcess *youtubeDl = new QProcess();
        youtubeDl->setArguments({"-f", "bestaudio", "--no-part", "-o", path.c_str(), url.c_str()});
        youtubeDl->setProgram("youtube-dl");
        youtubeDl->start();

        this->connect(youtubeDl,  static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), [=](int code, QProcess::ExitStatus status){
            if(status != QProcess::ExitStatus::CrashExit && code == 0) {
                LOG(INFO) << "Music "<< url <<" completed";
                QSqlQuery update(this->m_db);
                update.prepare("UPDATE musics SET status = :status WHERE id = :id;");
                update.bindValue(":id", id);
                update.bindValue(":status", DOWNLOADED);
                update.exec();
                youtubeDl->deleteLater();
            }
            this->m_downloadingIds.erase(id);
        });

        return path;
    }
    return "";
}

std::string MediaCollection::downloadMedia(const std::string &url)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO musics(url, status) VALUES (:url, :status)");
    query.bindValue(":url", QString::fromStdString(url));
    query.bindValue(":status", DOWNLOADING);
    query.exec();
    int id = query.lastInsertId().toInt();
    std::string path = downloadMediaById(id);
    QThread::sleep(2);

    return path;
}

std::string MediaCollection::getMediaId(const std::string &url)
{
    QByteArray bytes;
    bytes.append(url.data());
    QByteArray hash = QCryptographicHash::hash(bytes, QCryptographicHash::Md5);

    return hash.toHex().toStdString();
}

void MediaCollection::restartIncompleteDownloads()
{
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM musics WHERE status = :status;");
    query.bindValue(":status", DOWNLOADING);
    query.exec();
    while(query.next())
    {
        downloadMediaById(query.value(0).toInt());
    }
}
