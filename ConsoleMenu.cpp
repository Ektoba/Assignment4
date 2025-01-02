#include "pch.h"
#include "ConsoleMenu.h"
#include "CKeyMgr.h"
#include "ConsoleRender.h"
#include "ConsoleRender.h"
#include "App.h"
CConsoleMenu::CConsoleMenu(CConsoleRender* Render) :
	CConsoleObject(Render)
{
}

CConsoleMenu::~CConsoleMenu()
{
	//std::cout << "CConsoleMenu �Ҹ�" << std::endl;
}
void CConsoleMenu::init()
{
	m_Select = 1;
	CConsoleObject::init();
	m_vecText.push_back("=============================================================================================\n");
	size_t size = m_vecText[0].size();
	m_vecText.push_back(GetPaddingAppendText(size, "1. å ���"));
	m_vecText.push_back(GetPaddingAppendText(size, "2. å �뿩"));
	m_vecText.push_back(GetPaddingAppendText(size, "3. ���α׷� ����"));
	m_vecText.push_back("=============================================================================================\n");
}

void CConsoleMenu::update(HANDLE hConsole)
{
	
	if (CKeyMgr::GetInst()->GetKeyState(KEY::W) == KEY_STATE::TAP && m_Select > 1)
	{
		--m_Select;
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY::S) == KEY_STATE::TAP && m_Select < 3)
	{
		++m_Select;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
	{
		m_Select != NONE ? m_Render->ChangeScene((SCENE)(m_Select)) : CApp::GetInst()->AppEnd();
	}
}
