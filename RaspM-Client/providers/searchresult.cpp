#include "searchresult.h"

SearchResult::SearchResult(QObject* parent, QString p_url, QString p_title, QString p_thumb):
    QObject(parent), m_url(p_url), m_title(p_title), m_thumb(p_thumb)
{}
