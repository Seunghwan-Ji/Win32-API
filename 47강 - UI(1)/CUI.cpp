#include "CUI.h"

CUI::CUI()
	: m_pParentUI(nullptr)
{
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI); // 자식 UI 벡터 삭제.
}

void CUI::update()
{
	update_child();
}

void CUI::finalupdate()
{
	CObject::finalupdate(); // 애니메이션을 보유한 UI 를 위해 호출.

	// UI 의 최종 좌표를 구한다.
	// 최종 좌표 = 부모 좌표 + 부모로부터 떨어어진 거리.
	m_vFinalPos = GetPos(); // 부모가 없는 UI 의 최종 좌표.

	// 부모가 있을 경우.
	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos; // 부모의 위치도 더한다.
	}

	finalupdate_child();
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, int(vPos.x)
		, int(vPos.y)
		, int(vPos.x + vScale.x)
		, int(vPos.y + vScale.y));

	// 부모 UI 의 렌더링이 끝나면, 자식 UI 렌더링.
	render_child(_dc);
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}