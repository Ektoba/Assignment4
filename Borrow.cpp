#include "pch.h"
#include "Borrow.h"
#include "ConsoleRender.h"
#include "CKeyMgr.h"
#include "BookManager.h"
#include "Book.h"
CBorrow::CBorrow() :
	m_mapBook{},
	m_vecTitle{},
	m_vecAuthor{}
{
}

CBorrow::CBorrow(CConsoleRender* Render) :
	CConsoleObject(Render),
	m_mapBook{},
	m_vecTitle{},
	m_vecAuthor{}
{
}

CBorrow::~CBorrow()
{
	//std::cout << "CBorrow 소멸" << std::endl;
}

void CBorrow::init()
{
	CConsoleObject::init();

	CBookManager::GetInst()->InitStock();

	m_mapBook = &CBookManager::GetInst()->getAllStock();

	init_text();
	
	m_Select = 1;
	size_t size = m_vecText.back().size();
	m_vecMenu.push_back(GetPaddingAppendText(size, "| - 책 대출 : B"));
	m_vecMenu.push_back(GetPaddingAppendText(size, "| - 책 반납 : R"));
	m_vecMenu.push_back(GetPaddingAppendText(size, "| - 메뉴    : Q"));
	m_vecMenu.push_back(GetPaddingAppendText(size, "| - 종료    : ESC"));
	m_vecMenu.push_back("==========================================================================================================\n");
}

void CBorrow::update(HANDLE hConsole)
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY::W) == KEY_STATE::TAP && m_Select > 1)
	{
		--m_Select;
	}

	else if (CKeyMgr::GetInst()->GetKeyState(KEY::S) == KEY_STATE::TAP && m_Select < m_vecText.size() - 2)
	{
		++m_Select;
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY::Q) == KEY_STATE::TAP && m_Select < m_vecText.size() - 2)
	{
		m_Render->ChangeScene(SCENE::MENU);
	}

	else if (CKeyMgr::GetInst()->GetKeyState(KEY::B) == KEY_STATE::TAP)
	{
		std::string title = m_vecTitle[m_Select - 1];
		std::string author = m_vecAuthor[m_Select - 1];
		CBookManager::GetInst()->borrowBook(title);
		init_text();
	}

	else if (CKeyMgr::GetInst()->GetKeyState(KEY::R) == KEY_STATE::TAP)
	{
		std::string title = m_vecTitle[m_Select - 1];
		std::string author = m_vecAuthor[m_Select - 1];
		CBookManager::GetInst()->returnBook(title);
		init_text();
	}
}

void CBorrow::init_text()
{
	m_vecAuthor.clear();
	m_vecTitle.clear();
	m_vecText.clear();

	auto iter = m_mapBook->begin();
	auto iter_end = m_mapBook->end();

	size_t size = NULL;
	m_vecText.push_back("==========================================================================================================\n");

	for (; iter != iter_end; ++iter)
	{
		std::ostringstream oss;
		auto val = (*iter);
		CBook* book = val.first;
		m_vecTitle.push_back(book->getTitle());
		m_vecAuthor.push_back(book->getAuthor());
		std::string title = "title : " + m_vecTitle.back();
		std::string author = " author : " + m_vecAuthor.back();
		std::string stock = " stock : " + std::to_string(val.second);

		oss << title << std::string(70 - title.size(), ' ') << author << std::string(25 - author.size(), ' ') << stock << "\n";
		m_vecText.push_back(oss.str());
	}
	m_vecText.push_back("==========================================================================================================\n");
}
