#include "searchresult.h"

SearchResult::SearchResult(QObject* parent, QString p_url, QString p_title, QString p_thumb):
    QObject(parent), m_url(p_url), m_title(p_title), m_thumb(p_thumb)
{}

SearchResult::SearchResult(const SearchResult &other): QObject(other.parent()), m_url(other.m_url), m_title(other.m_title), m_thumb(other.m_thumb)
{

}

SearchResult &SearchResult::operator=(const SearchResult &other)
{
    m_thumb = other.m_thumb;
    m_title = other.m_title;
    m_url = other.m_url;
    return *this;
}
