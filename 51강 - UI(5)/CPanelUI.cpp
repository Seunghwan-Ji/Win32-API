#include "pch.h"
#include "CPanelUI.h"
#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	: CUI(false) // 부모인 CUI 는 설계상 기본 생성자가 없기 떄문에,
			     // 자식 UI 는 항상 이러한 형태의 부모 생성자를 호출해야 한다.
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::MouseOn()
{
	if (IsLbtnDown())
	{
		// 거리 차이 계산.
		// 현재 마우스 위치 - 드래그 시점 마우스 위치.
		Vec2 vDiff = MOUSE_POS - m_vDragStart;

		// 거리 차이만큼 UI 이동.
		Vec2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		// 드래그 시점 마우스 좌표 갱신.
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