#ifndef YOUTUBESEARCHCLIENT_H
#define YOUTUBESEARCHCLIENT_H

#include "searchresult.h"

#include <QList>
#include <QNetworkAccessManager>

class YoutubeSearchClient: public QObject
{
    Q_OBJECT
public:
    YoutubeSearchClient();
    void search(QString query);
    void suggest(QString query);
signals:
    void searchResultReady(QString query, QList<SearchResult> results);
    void suggestResultReady(QString query, QStringList results);

private:
    QNetworkAccessManager m_mng;

};

#endif // YOUTUBESEARCHCLIENT_H
