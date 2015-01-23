#ifndef YOUTUBESEARCHCLIENT_H
#define YOUTUBESEARCHCLIENT_H

#include "searchresult.h"

#include <QList>
#include <QNetworkAccessManager>

Q_DECLARE_METATYPE(SearchResult)

class YoutubeSearchClient: public QObject
{
    Q_OBJECT
public:
    YoutubeSearchClient(QObject* parent);

public slots:
    void search(QString query);
    void suggest(QString query);

signals:
    void searchResultReady(QString query, QVariantList results);
    void suggestResultReady(QString query, QStringList results);

private:
    QNetworkAccessManager m_mng;

};

#endif // YOUTUBESEARCHCLIENT_H
