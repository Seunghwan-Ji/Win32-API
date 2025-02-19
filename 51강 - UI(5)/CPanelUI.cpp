#include "pch.h"
#include "CPanelUI.h"
#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	: CUI(false) // �θ��� CUI �� ����� �⺻ �����ڰ� ���� ������,
			     // �ڽ� UI �� �׻� �̷��� ������ �θ� �����ڸ� ȣ���ؾ� �Ѵ�.
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::MouseOn()
{
	if (IsLbtnDown())
	{
		// �Ÿ� ���� ���.
		// ���� ���콺 ��ġ - �巡�� ���� ���콺 ��ġ.
		Vec2 vDiff = MOUSE_POS - m_vDragStart;

		// �Ÿ� ���̸�ŭ UI �̵�.
		Vec2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		// �巡�� ���� ���콺 ��ǥ ����.
		m_vDragStart = MOUSE_POS;
	}
}

void CPanelUI::MouseLbtnDown()
{
	m_vDragStart = MOUSE_POS;
}

void CPanelUI::MouseLbtnUp()
{
}