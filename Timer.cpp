#include "pch.h"
#include "Timer.h"


CTimer::CTimer()
{
	m_last = std::chrono::steady_clock::now();

}

CTimer::~CTimer()
{

}

float CTimer::Mark()
{
	const auto old = m_last;
	m_last = std::chrono::steady_clock::now();
	std::chrono::duration<float> delta = m_last - old;

	return delta.count();
}

float CTimer::Peek()
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - m_last).count();
}