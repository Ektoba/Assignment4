#pragma once
#include "ConsoleObject.h"
class CConsoleMenu :
    public CConsoleObject
{
    friend class CConsoleRender;
public:
    CConsoleMenu(class CConsoleRender* Render);
    ~CConsoleMenu();
private:
    virtual void init() override;
public:
    virtual void update(HANDLE hConsole) override;
};

