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
	// ��� �ʱ�ȭ.
	void InitStock(CBook* book);
	// å�� ������ ���.
	void borrowBook(const std::string& title);
	// å�� �ݳ��ϴ� ���
	void returnBook(const std::string& title);
	// ����å�� ����ϴ� ���.
	std::unordered_map<class CBook*, int>& getAllStock();
};

