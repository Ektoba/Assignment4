#include "pch.h"
#include "CKeyMgr.h"

int g_iVK[(UINT)KEY::KEY_END] =
{
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',

	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',

	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',

	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,

	VK_LSHIFT,
	VK_LMENU,
	VK_LCONTROL,	
	VK_SPACE,
	VK_RETURN,
	VK_BACK,
	VK_ESCAPE,
	VK_TAB,	

	VK_LBUTTON,
	VK_RBUTTON,
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{

}

bool CKeyMgr::Init()
{
	for (UINT i = 0; i < (UINT)KEY::KEY_END; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false } );
	}	
	return true;
}

void CKeyMgr::update(HANDLE Handle)
{
	HWND hFocusedHwnd = GetFocus();

	if (Handle)
	{
		for (UINT i = 0; i < (UINT)KEY::KEY_END; ++i)
		{
			// 키가 눌려있다
			if (GetAsyncKeyState(g_iVK[i]) & 0x8000)
			{
				// 이전엔 눌린적이 없다.
				if (false == m_vecKey[i].bPrevCheck)
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::PRESSED;
				}

				m_vecKey[i].bPrevCheck = true;
			}

			// 키가 안눌려있다.
			else
			{
				// 이전엔 눌려있었다.
				if (KEY_STATE::TAP == m_vecKey[i].eState
					|| KEY_STATE::PRESSED == m_vecKey[i].eState)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else if (KEY_STATE::AWAY == m_vecKey[i].eState)
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevCheck = false;
			}
		}
	}
		
	// 윈도우가 포커싱 되어있지 않다.
	else
	{
		for (UINT i = 0; i < (UINT)KEY::KEY_END; ++i)
		{
			m_vecKey[i].bPrevCheck = false;
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::PRESSED == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}

			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}