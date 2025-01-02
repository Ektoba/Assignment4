#pragma once
#include "BookManager.h"
class CBorrowManager
{
public:
	friend class CBookManager;
public:
	CBorrowManager();
	~CBorrowManager();
private:
	std::unordered_map<class CBook*,int> m_mapStock;
public:
	bool Init();
	// 재고 초기화.
	void InitStock(CBook* book);
	// 책을 빌리는 기능.
	void borrowBook(const std::string& title);
	// 책을 반납하는 기능
	void returnBook(const std::string& title);
	// 빌린책을 출력하는 기능.
	std::unordered_map<class CBook*, int>& getAllStock();
};

