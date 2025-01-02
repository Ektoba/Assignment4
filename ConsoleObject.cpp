#include "pch.h"
#include "ConsoleObject.h"
#include "ConsoleRender.h"

CConsoleObject::CConsoleObject() :
	m_TextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY),
	m_BackGroundColor(NULL),
	m_hConsole(NULL),
	m_vecText{},
	m_vecMenu{},
	m_Select(NULL)
{
}

CConsoleObject::CConsoleObject(CConsoleRender* Render) :
	m_TextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY),
	m_BackGroundColor(NULL),
	m_Render(Render),
	m_hConsole(NULL),
	m_vecText{},
	m_vecMenu{},
	m_Select(NULL)
{
}

CConsoleObject::~CConsoleObject()
{

}

void CConsoleObject::init()
{
	m_TextColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
}

std::string CConsoleObject::GetPaddingAppendText(size_t size, const std::string& dest)
{
	std::ostringstream oss;
	std::string result;
	
	size_t dest_size = dest.size();
	size_t padding = size - dest_size - '\n' + 8;
	oss << dest << std::string(padding, ' ');
	result = oss.str() + "|\n";

	return result;
}

void CConsoleObject::update(HANDLE hConsole)
{

}

void CConsoleObject::render(HANDLE hConsole)
{
	size_t size = m_vecText.size();
	DWORD dw;
	COORD pos = {};
	SetConsoleCursorPosition(hConsole, pos);

	for (size_t i = 0; i < size; ++i)
	{
		if (i == m_Select)
		{
			m_Render->SetTextColorAndBackGroundColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY, m_BackGroundColor);
		}
		else
		{
			m_Render->SetTextColorAndBackGroundColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}

		WriteFile(hConsole, m_vecText[i].c_str(), (DWORD)m_vecText[i].size(), &dw, NULL);
		m_Render->SetTextColorAndBackGroundColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	size = m_vecMenu.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_Render->SetTextColorAndBackGroundColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		WriteFile(hConsole, m_vecMenu[i].c_str(), (DWORD)m_vecMenu[i].size(), &dw, NULL);
		m_Render->SetTextColorAndBackGroundColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
}