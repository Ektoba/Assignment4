#pragma once
#include "ConsoleRender.h"
class CConsoleRender;

class CConsoleObject
{
protected:
	friend class CConsoleRender;
protected:
	CConsoleObject();
	CConsoleObject(CConsoleRender* Render);
public:
	virtual ~CConsoleObject();
protected:
	virtual void init();
	std::string GetPaddingAppendText(size_t size, const std::string& dest);
public:
	virtual void update(HANDLE hConsole);
	virtual void render(HANDLE hConsole);
protected:
	CConsoleRender*		     m_Render;
	HANDLE                   m_hConsole;
	std::vector<std::string> m_vecText;
	std::vector<std::string> m_vecMenu;
	WORD                     m_TextColor;
	WORD                     m_BackGroundColor;
	int                      m_Select = 1;
};

