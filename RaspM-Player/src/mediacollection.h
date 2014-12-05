#ifndef MEDIACOLLECTION_H
#define MEDIACOLLECTION_H
#include <map>
#include <string>
#include <QObject>

class MediaCollection: public QObject
{
public:
    MediaCollection(const std::string &cacheFolder);
    MediaCollection();
    void setCacheFolder(const std::string &path);
    std::string getMediaFilePath(const std::string& url);
    void save();
    void load();

private:
    std::string downloadMedia(const std::string &url);
    std::string getMediaId(const std::string &url);

private:
    std::map<std::string, std::string> m_mediasUrls;
    std::string m_cacheFolder;
};

#endif // MEDIACOLLECTION_H
