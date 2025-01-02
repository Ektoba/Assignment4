#include "pch.h"
#include "BookContainer.h"
#include "Book.h"

CBookContainer::CBookContainer()
{
}

CBookContainer::~CBookContainer()
{
    m_vecBook.clear();
}

void CBookContainer::addBook(const std::string& title, const std::string& author)
{
    m_vecBook.push_back(std::move(std::make_unique<CBook>(title, author)));
}

std::vector<CBook*> CBookContainer::findBookByTitle(const std::string& title)
{
    auto iter_end = m_vecBook.end();
    std::vector<CBook*> vecBook;
    for (auto iter = m_vecBook.begin(); iter != iter_end; ++iter)
    {
        if ((*iter).get()->getTitle() == title)
        {
            CBook* book = (*iter).get();
            vecBook.push_back(book);
        }
    }

    return vecBook;
}

std::vector<CBook*> CBookContainer::findBookByAuthor(const std::string& author)
{
    auto iter_end = m_vecBook.end();
    std::vector<CBook*> vecBook;
    for (auto iter = m_vecBook.begin(); iter != iter_end; ++iter)
    {
        if ((*iter).get()->getAuthor() == author)
        {
            CBook* book = (*iter).get();
            vecBook.push_back(book);
        }
    }

    return vecBook;
}

std::vector<class CBook*> CBookContainer::getAllBooks()
{
    std::vector<CBook*> vecBook;
    auto iter = m_vecBook.begin();
    auto iter_end = m_vecBook.end();

    for (; iter != iter_end; ++iter)
    {
        vecBook.push_back((*iter).get());
    }
    return vecBook;
}

void CBookContainer::sort()
{
    std::stable_sort(m_vecBook.begin(), m_vecBook.end(), [](const PBOOK& a, const PBOOK& b)->bool
    {
        if (a->getTitle() == b->getTitle())
        {
            return a->getAuthor().size() <= b->getAuthor().size();
        }
        else
            return a->getTitle().size() <= b->getTitle().size();
    });
}
