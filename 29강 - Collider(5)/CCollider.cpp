#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++) // 정적 변수의 특성을 이용해 객체마다 고유 ID 값을 다르게 설정.
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr) // 충돌 영역의 주인이 되는 오브젝트는 복사하지 않는다.
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++) // 복사 했더라도 고유 ID 값은 다르게 설정한다.
{
}

CCollider::~CCollider()
{
}

void CCollider::finalupdate()
{
	// 오브젝트의 위치를 따라간다.
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void CCollider::render(HDC _dc)
{
	// 지역 변수 없이 생성하는 임시 객체.
	SelectGDI p(_dc, PEN_TYPE::GREEN);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc
		, (int)(m_vFinalPos.x - m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y - m_vScale.y / 2.f)
		, (int)(m_vFinalPos.x + m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y + m_vScale.y / 2.f));
}

void CCollider::OnCollision(CCollider* _pOther)
{
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
}
