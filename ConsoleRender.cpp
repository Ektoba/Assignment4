#include "pch.h"
#include "ConsoleRender.h"
#include "ConsoleMenu.h"
#include "BookViewer.h"
#include "CKeyMgr.h"
#include "Borrow.h"

CConsoleRender::CConsoleRender() :
    m_Console{},
    m_cci{},
    m_Pos{},
    m_Scene(SCENE::MENU)
{
}

CConsoleRender::~CConsoleRender()
{
    ScreenRelease();

    size_t size = m_vecObj.size();

    for (size_t i = 0; i < size; ++i)
    {
        m_vecObj[i].reset();
    }
    m_vecObj.clear();
}

bool CConsoleRender::Init()
{
    ScreenInit();
    m_vecObj.resize(SCENE::NONE);
    m_vecObj[SCENE::MENU] = std::make_unique<CConsoleMenu>(this);
    m_vecObj[SCENE::MENU]->init();
    m_vecObj[SCENE::BOOK_VIEWER] = std::make_unique<CBookViewer>(this);
    m_vecObj[SCENE::BOOK_VIEWER]->init();
    m_vecObj[SCENE::BORROW] = std::make_unique<CBorrow>(this);
    m_vecObj[SCENE::BORROW]->init();

    return true;
}

void CConsoleRender::Update(const float DeltaTime)
{
    m_vecObj[m_Scene]->update(m_Console.hBuffer[m_Console.nBufferIdx]);
}

void CConsoleRender::Render(const float DeltaTime)
{
    ScreenClear();
    ScreenPrint();
    ScreenFlipping();
}

void CConsoleRender::SetTextColorAndBackGroundColor(WORD foregroundColor, WORD backgroundColor)
{
    WORD colorAttribute = foregroundColor | backgroundColor;
    SetConsoleTextAttribute(m_Console.hBuffer[m_Console.nBufferIdx], colorAttribute);
}

void CConsoleRender::ChangeScene(const SCENE& Scene)
{
    m_vecObj[m_Scene].reset();

    switch (m_Scene)
    {
    case MENU:
        m_vecObj[SCENE::MENU] = std::make_unique<CConsoleMenu>(this);
        break;
    case BOOK_VIEWER:
        m_vecObj[SCENE::BOOK_VIEWER] = std::make_unique<CBookViewer>(this);
        break;
    case BORROW:
        m_vecObj[SCENE::BORROW] = std::make_unique<CBorrow>(this);
        break;
    case NONE:
        break;
    default:
        break;
    }
    m_vecObj[m_Scene]->init();
    m_Scene = Scene;
}

std::string CConsoleRender::InputText(const std::string& text)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hOutput2 = m_Console.hBuffer[m_Console.nBufferIdx];

    SetConsoleActiveScreenBuffer(hOutput2);
    if (hInput == INVALID_HANDLE_VALUE || hOutput2 == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error: Invalid console handle." << std::endl;
        return "Error: Invalid console handle.";
    }

    configureConsoleForRawInput(hInput);
    FlushConsoleInputBuffer(hInput);
    char inputBuffer[256] = {};
    DWORD bytesRead;
    std::string inputText = "";
    PrintText(hOutput2, text);
    while (true) 
    {
        PrintText(hOutput2, inputBuffer);
        // Read input
        if (ReadFile(hInput, inputBuffer, sizeof(inputBuffer) - 1, &bytesRead, NULL)) {
            inputBuffer[bytesRead] = '\0'; // Null-terminate input
            if (strchr(inputBuffer, '\r'))
            {
                inputText += '\0';
                PrintText(hOutput2, "\n");
                break;
            }
            else
                inputText += std::string(inputBuffer);
        }
        else {
            std::cerr << "Error: ReadFile failed." << std::endl;
            break;
        }
    }
    return inputText;
}

void CConsoleRender::configureConsoleForRawInput(HANDLE hInput)
{
    DWORD mode;
    if (!GetConsoleMode(hInput, &mode)) 
    {
        std::cerr << "Error: Could not get console mode." << std::endl;
        return;
    }

    // Disable line buffering and echo
    mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    if (!SetConsoleMode(hInput, mode)) 
    {
        std::cerr << "Error: Could not set console mode." << std::endl;
    }
}

void CConsoleRender::ScreenInit()
{
    m_cci.dwSize = 1;       // 깜빡임 제거
    m_cci.bVisible = FALSE; //콘솔 숨기기

    m_Console.hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    m_Console.nBufferIdx = 0;

    m_Console.hInput = GetStdHandle(STD_INPUT_HANDLE);

    // 콘솔 관련 설정
    CONSOLE_CURSOR_INFO consoleCursor{ 1, FALSE };  // 콘솔의 커서 깜빡임을 제거합니다.
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo{};
    GetConsoleScreenBufferInfo(m_Console.hConsole, &consoleInfo);
    consoleInfo.dwSize.X = 1280;                    // 콘솔의 Width
    consoleInfo.dwSize.Y = 720;                     // 콘솔의 Height

    // 콘솔의 크기를 다시 계산 (나중에 그림 그릴때 사용)
    m_Console.rtConsole.nWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left;
    m_Console.rtConsole.nHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top;

    // 콘솔의 첫번째 화면 버퍼 생성
    m_Console.hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleScreenBufferSize(m_Console.hBuffer[0], consoleInfo.dwSize);    // 화면 버퍼 크기 설정
    SetConsoleWindowInfo(m_Console.hBuffer[0], TRUE, &consoleInfo.srWindow); // 콘솔 설정
    SetConsoleCursorInfo(m_Console.hBuffer[0], &consoleCursor);              // 콘솔의 커서 설정

    // 콘솔의 두번째 화면 버퍼 생성
    m_Console.hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleScreenBufferSize(m_Console.hBuffer[1], consoleInfo.dwSize);
    SetConsoleWindowInfo(m_Console.hBuffer[1], TRUE, &consoleInfo.srWindow);
    SetConsoleCursorInfo(m_Console.hBuffer[1], &consoleCursor);
}

void CConsoleRender::ScreenFlipping()
{    
    SetConsoleActiveScreenBuffer(m_Console.hBuffer[m_Console.nBufferIdx]);
    m_Console.nBufferIdx = (int)!m_Console.nBufferIdx;
}

void CConsoleRender::PrintText(HANDLE hOutput, const std::string& string)
{
    DWORD dw;
    WriteFile(m_Console.hBuffer[m_Console.nBufferIdx], string.c_str(), (DWORD)string.size(), &dw, NULL);
}

void CConsoleRender::ScreenClear()
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo{};
    GetConsoleScreenBufferInfo(m_Console.hBuffer[m_Console.nBufferIdx], &consoleInfo);

    COORD pos{};
    DWORD dwWritten = 0;
    unsigned size = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;

    // 콘솔 화면 전체를 띄어쓰기를 넣어 빈 화면처럼 만듭니다.
    FillConsoleOutputCharacter(m_Console.hBuffer[m_Console.nBufferIdx], ' ', size, pos, &dwWritten);
    SetConsoleCursorPosition(m_Console.hBuffer[m_Console.nBufferIdx], pos);
}

void CConsoleRender::setCursorPosition(const short x, const short y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(m_Console.hBuffer[m_Console.nBufferIdx], pos);
}

void CConsoleRender::ScreenRelease()
{
    if (m_Console.hBuffer[0])
    {
        CloseHandle(m_Console.hBuffer[0]);
    }
    if (m_Console.hBuffer[1])
    {
        CloseHandle(m_Console.hBuffer[1]);
    }
}

void CConsoleRender::ScreenPrint()
{
    m_vecObj[m_Scene]->render(m_Console.hBuffer[m_Console.nBufferIdx]);
}