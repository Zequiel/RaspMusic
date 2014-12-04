#ifndef MEDIACOLLECTION_H
#define MEDIACOLLECTION_H
#include <map>
#include <string>

class MediaCollection
{
public:
    MediaCollection(const std::string &cacheFolder);
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
