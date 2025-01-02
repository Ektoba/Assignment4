#pragma once
#include "ConsoleObject.h"
class CBorrow :
    public CConsoleObject
{
public:
    CBorrow();
    CBorrow(class CConsoleRender* Render);
    ~CBorrow();
private:
    virtual void init();
public:
    virtual void update(HANDLE hConsole) override;
private:
    std::unordered_map<class CBook*, int>* m_mapBook;
    std::vector<std::string>               m_vecTitle;
    std::vector<std::string>               m_vecAuthor;
private:
    void init_text();
};

