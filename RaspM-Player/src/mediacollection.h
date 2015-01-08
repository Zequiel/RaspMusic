#ifndef MEDIACOLLECTION_H
#define MEDIACOLLECTION_H
#include <map>
#include <set>
#include <string>
#include <QObject>
#include <QSqlDatabase>

class MediaCollection: public QObject
{
public:
    MediaCollection(const std::string &cacheFolder);
    MediaCollection();
    ~MediaCollection();
    void setCacheFolder(const std::string &path);
    std::string getMediaFilePath(const std::string& url);
    void load();

    std::string downloadMediaById(int id);
private:
    std::string downloadMedia(const std::string &url);
    std::string getMediaId(const std::string &url);
    void restartIncompleteDownloads();

private:
    std::map<std::string, std::string> m_mediasUrls;
    std::string m_cacheFolder;
    std::set<int> m_downloadingIds;
    QSqlDatabase m_db;
};

#endif // MEDIACOLLECTION_H
