#pragma once
class CTimer
{
	friend class CTimeManager;
private:
	CTimer();
	~CTimer();

	float Mark();
	float Peek();

private:
	std::chrono::steady_clock::time_point m_last;
};

