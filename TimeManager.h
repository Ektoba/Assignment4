#pragma once
#include "Timer.h"

class CTimeManager
{
	friend class CApp;
public:
	CTimeManager();
	~CTimeManager();
private:
	float m_DeltaTime;
	CTimer m_Timer;
private:
	bool Init();
	float GetDeltaTime();
};

