#include "pch.h"
#include "Book.h"

CBook::CBook(const std::string& title, const std::string& author) :
    m_title(title),
    m_author(author)
{
}

CBook::~CBook()
{
}

std::string CBook::getTitle() const
{
    return m_title;
}

std::string CBook::getAuthor() const
{
    return m_author;
}
