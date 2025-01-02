#include "pch.h"
#include "TimeManager.h"

CTimeManager::CTimeManager()
{
	m_DeltaTime = m_Timer.Mark();
}

CTimeManager::~CTimeManager()
{
}

bool CTimeManager::Init()
{
	return true;
}

float CTimeManager::GetDeltaTime()
{
	return m_Timer.Mark();
}
