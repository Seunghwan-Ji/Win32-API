#include "pch.h"
#include "CKeyMgr.h"

// 실제 윈도우 가상키 값과 매칭하기 위한 용도.
int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,  // LEFT
	VK_RIGHT, // RIGHT
	VK_UP,    // UP
	VK_DOWN,  // DOWN

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
	'Z',
	'X',

	VK_MENU,	// ALT
	VK_CONTROL, // CTRL
	VK_LSHIFT,	// LEFT SHIFT
	VK_SPACE,	// SPACE
	VK_RETURN,	// ENTER
	VK_ESCAPE,	// ESC
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		// 벡터에 모든 키 정보 추가.
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		// 키가 눌려있다.
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
		{
			if (m_vecKey[i].bPrevPush)
			{
				// 이전에도 눌려있었다.
				m_vecKey[i].eState = KEY_STATE::HOLD;
			}
			else
			{
				// 이전에 눌려있지 않았다.
				m_vecKey[i].eState = KEY_STATE::TAP;
			}

			// 다음 프레임에서 참조하기 위해 값 지정.
			m_vecKey[i].bPrevPush = true;
		}
		else
		{
			if (m_vecKey[i].bPrevPush)
			{
				// 이전에 눌려있었다.
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else
			{
				// 이전에도 안 눌려있었다.
				m_vecKey[i].eState = KEY_STATE::NONE;
			}

			m_vecKey[i].bPrevPush = false;
		}
	}
}
