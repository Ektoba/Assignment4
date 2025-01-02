#include "pch.h"
#include "BookManager.h"
#include "BookContainer.h"
#include "BorrowManager.h"

CBookManager::CBookManager()
{

}

CBookManager::~CBookManager()
{
	m_Borrow.reset();
	m_Container.reset();
}

bool CBookManager::Init()
{
	m_Borrow = std::make_unique<CBorrowManager>();
	m_Container = std::make_unique<CBookContainer>();
	return true;
}

void CBookManager::InitStock()
{
	std::vector<CBook*> vecBook = getAllBooks();
	size_t size = vecBook.size();

	for (size_t i = 0; i < size; ++i)
	{
		m_Borrow->InitStock(vecBook[i]);
	}
}

void CBookManager::borrowBook(const std::string& title)
{
	m_Borrow->borrowBook(title);
}

void CBookManager::returnBook(const std::string& title)
{
	m_Borrow->returnBook(title);
}

void CBookManager::addBook(const std::string& title, const std::string& author)
{
	m_Container->addBook(title, author);
}

std::vector<CBook*> CBookManager::findBookByTitle(const std::string& title)
{
	return m_Container->findBookByTitle(title);
}

std::vector<CBook*> CBookManager::findBookByAuthor(const std::string& author)
{
	return m_Container->findBookByAuthor(author);
}

std::vector<CBook*> CBookManager::getAllBooks()
{
	return m_Container->getAllBooks();
}

std::unordered_map<CBook*, int>& CBookManager::getAllStock()
{
	return m_Borrow->getAllStock();
}
