#include "youtubesearchclient.h"
#include <QtNetwork>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QJsonArray>
#include <QJsonDocument>
#include<iostream>

YoutubeSearchClient::YoutubeSearchClient(QObject* parent): QObject(parent)
{
}

void YoutubeSearchClient::search(QString query)
{
    QUrl url("https://www.googleapis.com/youtube/v3/search");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("q", query);
    urlQuery.addQueryItem("part","snippet");
    urlQuery.addQueryItem("type","video");
    urlQuery.addQueryItem("key","AIzaSyCKUqjCWD_DZa2amJUVLg8hKYEheB5IOLI");
    urlQuery.addQueryItem("maxResults","50");
    url.setQuery(urlQuery);

    QNetworkRequest request(url);
    QNetworkReply *response = m_mng.get(request);

    QObject::connect(response, &QNetworkReply::finished, [=](){
        QUrl youtubeUrl("https://www.youtube.com/watch");
        QJsonDocument doc = QJsonDocument::fromJson(response->readAll());
        response->deleteLater();
        auto items = doc.object()["items"].toArray();
        QVariantList results;
        for(const auto &element: items) {
            auto object = element.toObject();
            QString id = object["id"].toObject()["videoId"].toString();
            QString title = object["snippet"].toObject()["title"].toString();
            QString thumb = object["snippet"].toObject()["thumbnails"].toObject()["medium"].toObject()["url"].toString();

            QUrlQuery urlQuery;

            urlQuery.addQueryItem("v", id);
            youtubeUrl.setQuery(urlQuery);

            QVariant result;
            result.setValue(new SearchResult(this, youtubeUrl.toDisplayString(), title, thumb));

            results << result;
        }
        emit searchResultReady(query, results);
    });
}

void YoutubeSearchClient::suggest(QString query)
{
    QUrl url("https://suggestqueries.google.com/complete/search");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("q", query);
    urlQuery.addQueryItem("client","youtube");
    urlQuery.addQueryItem("ds","yt");
    url.setQuery(urlQuery);

    QNetworkRequest request(url);
    QNetworkReply *response = m_mng.get(request);
    QObject::connect(response, &QNetworkReply::finished, [=]() {
        QString content = response->readAll();
        response->deleteLater();
        QRegularExpression rg("^.*\\(\\[\".*\", (\\[\\[.*\\]\\]).*\\]\\)$", QRegularExpression::DotMatchesEverythingOption
                              | QRegularExpression::ExtendedPatternSyntaxOption);
        QRegularExpressionMatch match = rg.match(content);
        QString jsonArray = match.captured(1);
        QJsonDocument doc = QJsonDocument::fromJson(jsonArray.toUtf8());
        QStringList suggests;
        for(const QJsonValue &value: doc.array()) {
            suggests << value.toArray()[0].toString();
        }
        emit suggestResultReady(query, suggests);
    });
}
