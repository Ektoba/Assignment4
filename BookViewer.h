#pragma once
#include "ConsoleObject.h"
class CBookViewer :
    public CConsoleObject
{
public:
    CBookViewer();
    CBookViewer(class CConsoleRender* Render);
    ~CBookViewer();
private:
    void init();
    virtual void update(HANDLE hConsole) override;
};