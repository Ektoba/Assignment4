#include "pch.h"
#include "BorrowManager.h"
#include "Book.h"
CBorrowManager::CBorrowManager()
{
}

CBorrowManager::~CBorrowManager()
{
	m_mapStock.clear();
}

bool CBorrowManager::Init()
{
	return true;
}

void CBorrowManager::InitStock(CBook* book)
{
	auto iter = m_mapStock.find(book);
	auto iter_end = m_mapStock.end();

	if (iter == iter_end)
	{
		m_mapStock.insert(std::make_pair(book, 3));
	}
	else
	{
		(*iter).second += 1;
	}
}

void CBorrowManager::borrowBook(const std::string& title)
{
	CBook* book = nullptr;

	auto iter = m_mapStock.begin();
	auto iter_end = m_mapStock.end();

	for (; iter != iter_end; ++iter)
	{
		book = iter->first;

		if (book->getTitle() == title)
		{
			break;
		}
	}

	if (iter == iter_end || book == nullptr)
		return;

	if (iter->second > 0)
		iter->second -=1;
}

void CBorrowManager::returnBook(const std::string& title)
{
	CBook* book = nullptr;

	auto iter = m_mapStock.begin();
	auto iter_end = m_mapStock.end();

	for (; iter != iter_end; ++iter)
	{
		book = iter->first;

		if (book->getTitle() == title)
		{
			break;
		}
	}

	if (iter == iter_end || book == nullptr)
		return;

	if (iter->second >= 0 && iter->second < 3)
		iter->second += 1;
}

std::unordered_map<class CBook*, int>& CBorrowManager::getAllStock()
{
	return m_mapStock;
}