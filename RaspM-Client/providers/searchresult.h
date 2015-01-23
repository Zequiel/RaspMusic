#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QString>
#include <QObject>

struct SearchResult: public QObject
{
private:
    Q_OBJECT
    Q_PROPERTY(QString url MEMBER m_url)
    Q_PROPERTY(QString title MEMBER m_title)
    Q_PROPERTY(QString thumb MEMBER m_thumb)
public:
    SearchResult(QObject* parent, QString p_url, QString p_title, QString p_thumb);
private:
    QString m_url;
    QString m_title;
    QString m_thumb;
};

#endif // SEARCHRESULT_H
