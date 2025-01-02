#pragma once

enum SCENE
{
	MENU,
	BOOK_VIEWER,
	BORROW,
	NONE
};
class CConsoleRender
{
	friend class CApp;
private:
	struct stRect
	{
		unsigned int nWidth;
		unsigned int nHeight;
	};
	struct stConsole
	{
		HANDLE hConsole = nullptr;
		stRect rtConsole = {};
		HANDLE hBuffer[2] = {};
		HANDLE hInput = nullptr;
		int nBufferIdx = NULL;
	};
protected:

public:
	HANDLE getHandle()
	{
		return m_Console.hBuffer[m_Console.nBufferIdx];
	}
public:
	CConsoleRender();
	~CConsoleRender();
private:
	bool Init();
	void Update(const float DeltaTime);
	void Render(const float DeltaTime);
public:
	void SetTextColorAndBackGroundColor(WORD foregroundColor, WORD backgroundColor = NULL);
	void ScreenClear();
	void setCursorPosition(const short x, const short y);
public:
	void PrintText(HANDLE hOutput, const std::string& string);
	void ChangeScene(const SCENE& Scene);
	std::string InputText(const std::string& text);
private:
	SCENE                                              m_Scene;
	stConsole                                          m_Console = {};
	CONSOLE_CURSOR_INFO                                m_cci = {};
	COORD                                              m_Pos = {};
	std::vector<std::unique_ptr<class CConsoleObject>> m_vecObj;
public:
	void configureConsoleForRawInput(HANDLE hInput);
private:
	void ScreenInit();
	void ScreenFlipping();
	void ScreenRelease();
	void ScreenPrint();
};

