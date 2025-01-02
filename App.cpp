#include "pch.h"
#include "App.h"
#include "BookManager.h"
#include "TimeManager.h"
#include "ConsoleRender.h"
#include "CKeyMgr.h"
CApp::CApp() : 
	m_End(false)
{
}

CApp::~CApp()
{
	m_BookManager.reset();
	m_TimeManager.reset();
	m_ConsoleRender.reset();
}

bool CApp::Init()
{
	bool Init = false;
	Init = CBookManager::GetInst()->Init();
	PreAddBooks();
	m_TimeManager = std::make_unique<CTimeManager>();
	Init = m_TimeManager->Init();
	m_ConsoleRender = std::make_unique<CConsoleRender>();
	Init = m_ConsoleRender->Init();
	Init = CKeyMgr::GetInst()->Init();
	return Init;
}

int CApp::Run()
{
	while (!m_End)
	{
		m_DeltaTime = m_TimeManager->GetDeltaTime();
		PreUpdate(m_DeltaTime);
		Update(m_DeltaTime);
		Render(m_DeltaTime);
	}
	return NULL;
}

void CApp::PreUpdate(float DeltaTime)
{
	
}

void CApp::Update(float DeltaTime)
{
	CKeyMgr::GetInst()->update(m_ConsoleRender->getHandle());
	m_ConsoleRender->Update(DeltaTime);
}

void CApp::Render(float DeltaTime)
{
	m_ConsoleRender->Render(DeltaTime);
}

void CApp::AppEnd()
{
	m_End = true;
}

void CApp::PreAddBooks()
{
	CBookManager::GetInst()->addBook("윤성우의 열혈 C++", "윤성우");
	CBookManager::GetInst()->addBook("C++ 객체지향 프로그래밍", "송호근");
	CBookManager::GetInst()->addBook("대규모 C++ 1편 : 절차와 아키텍처", "존 레이코스");
	CBookManager::GetInst()->addBook("directx 11을 이용한 3d 게임 프로그래밍 입문", "프랭크 D 루나");
	CBookManager::GetInst()->addBook("셰이더 프로그래밍 입문", "Pope Kim");
	CBookManager::GetInst()->addBook("IT CookBook, 기본 개념과 핵심 원리로 배우는 C++ 프로그래밍", "김회수");
	CBookManager::GetInst()->addBook("C++ 프로그래밍(C로 접근하는)", "이대호");
	CBookManager::GetInst()->addBook("전문가를 위한 C++", "마크 그레고리");
}
