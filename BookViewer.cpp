#include "pch.h"
#include "BookViewer.h"
#include "BookManager.h"
#include "Book.h"
#include "ConsoleRender.h"
#include "CKeyMgr.h"
#include "App.h"

CBookViewer::CBookViewer()
{
}

CBookViewer::CBookViewer(CConsoleRender* Render) :
	CConsoleObject(Render)
{
	m_vecMenu.clear();
}

CBookViewer::~CBookViewer()
{
	//std::cout << "BookViewer 소멸" << std::endl;
}

void CBookViewer::init()
{
	m_Select = 1;
	CConsoleObject::init();
	auto vector = CBookManager::GetInst()->getAllBooks();
	m_TextColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	m_vecMenu = {};
	//m_BackGroundColor = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	size_t size = vector.size();
	for (size_t i = 0; i < size; ++i)
	{
		char buf[512];
		sprintf_s(buf, "Title : %-60s , Author : %s \n", vector[i]->getTitle().c_str(), vector[i]->getAuthor().c_str());
		m_vecText.push_back(buf);
	}
	m_vecMenu.push_back("=============================================================================================\n");
	size = m_vecMenu[0].size();
	m_vecMenu.push_back(GetPaddingAppendText(size, "| 선택     : space"));
	m_vecMenu.push_back(GetPaddingAppendText(size, "| 메뉴선택 : q"));
	m_vecMenu.push_back(GetPaddingAppendText(size, "| 책찾기   : f"));
	m_vecMenu.push_back(GetPaddingAppendText(size, "| 책추가   : a"));
	m_vecMenu.push_back(GetPaddingAppendText(size, "| 종료     : esc"));
	m_vecMenu.push_back("=============================================================================================\n");
}

void CBookViewer::update(HANDLE hConsole)
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY::W) == KEY_STATE::TAP && m_Select > 0)
	{
		--m_Select;
	}
	
	else if (CKeyMgr::GetInst()->GetKeyState(KEY::S) == KEY_STATE::TAP && m_Select < m_vecText.size()-1)
	{
		++m_Select;
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY::Q) == KEY_STATE::TAP)
	{		
		m_Render->ChangeScene(SCENE::MENU);
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY::F) == KEY_STATE::TAP)
	{
		std::string title = m_Render->InputText("찾을 책 제목 : ");
		std::vector<CBook*> vecBook = CBookManager::GetInst()->findBookByTitle(title);
		m_vecText.clear();
		size_t size = vecBook.size();
		if (size == 0)
		{
			m_vecText.push_back("찾으시는 책이 없습니다.\n");
		}
		for (size_t i = 0; i < size; ++i)
		{
			char buf[512];
			sprintf_s(buf, "Title : %-60s , Author : %s \n", vecBook[i]->getTitle().c_str(), vecBook[i]->getAuthor().c_str());
			m_vecText.push_back(buf);
		}
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY::A) == KEY_STATE::TAP)
	{
		std::string title = m_Render->InputText("추가할 책 제목 : ");
		std::string author = m_Render->InputText("추가할 책 저자 : ");
		std::vector<CBook*> vecBook = CBookManager::GetInst()->findBookByTitle(title);
		m_vecText.clear();
		size_t size = vecBook.size();

		CBookManager::GetInst()->addBook(title, author);
		m_vecText.push_back("책이 추가 되었습니다.");

		m_Render->ChangeScene(SCENE::BOOK_VIEWER);
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY::ESC) == KEY_STATE::TAP)
	{
		CApp::GetInst()->AppEnd();
	}
}

