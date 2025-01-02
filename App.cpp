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
	CBookManager::GetInst()->addBook("�������� ���� C++", "������");
	CBookManager::GetInst()->addBook("C++ ��ü���� ���α׷���", "��ȣ��");
	CBookManager::GetInst()->addBook("��Ը� C++ 1�� : ������ ��Ű��ó", "�� �����ڽ�");
	CBookManager::GetInst()->addBook("directx 11�� �̿��� 3d ���� ���α׷��� �Թ�", "����ũ D �糪");
	CBookManager::GetInst()->addBook("���̴� ���α׷��� �Թ�", "Pope Kim");
	CBookManager::GetInst()->addBook("IT CookBook, �⺻ ����� �ٽ� ������ ���� C++ ���α׷���", "��ȸ��");
	CBookManager::GetInst()->addBook("C++ ���α׷���(C�� �����ϴ�)", "�̴�ȣ");
	CBookManager::GetInst()->addBook("�������� ���� C++", "��ũ �׷���");
}
