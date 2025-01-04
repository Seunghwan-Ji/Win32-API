#include "pch.h"
#include "CKeyMgr.h"

// ���� ������ ����Ű ���� ��Ī�ϱ� ���� �뵵.
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
		// ���Ϳ� ��� Ű ���� �߰�.
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		// Ű�� �����ִ�.
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
		{
			if (m_vecKey[i].bPrevPush)
			{
				// �������� �����־���.
				m_vecKey[i].eState = KEY_STATE::HOLD;
			}
			else
			{
				// ������ �������� �ʾҴ�.
				m_vecKey[i].eState = KEY_STATE::TAP;
			}

			// ���� �����ӿ��� �����ϱ� ���� �� ����.
			m_vecKey[i].bPrevPush = true;
		}
		else
		{
			if (m_vecKey[i].bPrevPush)
			{
				// ������ �����־���.
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else
			{
				// �������� �� �����־���.
				m_vecKey[i].eState = KEY_STATE::NONE;
			}

			m_vecKey[i].bPrevPush = false;
		}
	}
}
