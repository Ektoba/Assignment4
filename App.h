#pragma once

class CApp :
	public CSingleton<CApp>
{
public:
	CApp();
	virtual ~CApp() override;
private:
	bool m_End = false;
	std::unique_ptr<class CBookManager>   m_BookManager;
	std::unique_ptr<class CTimeManager>   m_TimeManager;
	std::unique_ptr<class CConsoleRender> m_ConsoleRender;
	float m_DeltaTime = 0.f;
public:
	bool Init();
	int Run();
	void PreUpdate(float DeltaTime);
	void Update(float DeltaTime);
	void Render(float DeltaTime);
public:
	void AppEnd();
private:
	void PreAddBooks();
};

