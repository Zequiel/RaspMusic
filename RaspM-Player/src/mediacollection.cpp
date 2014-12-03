#include "mediacollection.h"
#include <QProcess>
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include <QVariantMap>

MediaCollection::MediaCollection()
{
    load();
}

std::string MediaCollection::getMediaFilePath(const std::string &url)
{
    auto it = m_mediasUrls.find(url);
    if(it != m_mediasUrls.end())
    {
        return it->second;
    }
    //TODO Configuration dossier de cache
    std::string path = downloadMedia(url, "/home/thomas/tmp");
    m_mediasUrls[url] = path;
    return path;
}

void MediaCollection::save()
{
    QSettings settings("RaspMusic", "Player");
    QMap<QString, QVariant> map;
    for(auto entry: m_mediasUrls)
    {
        map[QString::fromStdString(entry.first)] = QVariant(QString::fromStdString(entry.second));
    }
    settings.setValue("cacheData", map);
}

void MediaCollection::load()
{
    QSettings settings("RaspMusic", "Player");
    QMap<QString, QVariant> map = settings.value("cacheData").toMap();
    m_mediasUrls.clear();
    for(auto entry: map.toStdMap())
    {
        m_mediasUrls[entry.first.toStdString()] = entry.second.toString().toStdString();
    }
}

std::string MediaCollection::downloadMedia(const std::string &url, const std::string folder)
{
    std::string path = folder + "/%(id)s";
    std::string id = getMediaId(url);
    QProcess youtubeDl;
    youtubeDl.setArguments({"-f", "m4a", "-o", path.c_str(), url.c_str()});
    youtubeDl.setProgram("youtube-dl");
    youtubeDl.start();
    youtubeDl.waitForFinished(120000);

    std::string finalPath = folder + "/" + id;
    m_mediasUrls[url] = finalPath;
    save();
    return finalPath;
}

std::string MediaCollection::getMediaId(const std::string &url)
{
    QProcess youtubeDl;
    youtubeDl.setArguments({"-f", "m4a", "-j", url.c_str()});
    youtubeDl.setProgram("youtube-dl");
    youtubeDl.start();
    youtubeDl.waitForFinished(10000);
    QByteArray json = youtubeDl.readAllStandardOutput();
    QJsonDocument document = QJsonDocument::fromJson(json);
    QString id = document.object().value("display_id").toString();

    return id.toStdString();
}
