#include "CUI.h"
#include "CKeyMgr.h"
#include "CCamera.h"

CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCamAffected(false)
	, m_bMouseOn(false)
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

	// UI 마우스 체크
	MouseOnCheck();

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

	// 카메라에 영향을 받는 UI 이면, 렌더링 좌표로 변환.
	if (m_bCamAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

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

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	// 마우스가 UI 내부에 있는지 체크.
	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

// 중단점 걸고 마우스를 클릭하고 떼면서 각 함수로 들어오는지 확인.
void CUI::MouseOn()
{
}

void CUI::MouseLbtnDown()
{
}

void CUI::MouseLbtnUp()
{
}

void CUI::MouseLbtnClicked()
{
}
