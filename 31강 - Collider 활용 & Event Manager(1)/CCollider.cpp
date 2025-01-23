#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++) // ���� ������ Ư���� �̿��� ��ü���� ���� ID ���� �ٸ��� ����.
	, m_iCol(0)
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr) // �浹 ������ ������ �Ǵ� ������Ʈ�� �������� �ʴ´�.
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++) // ���� �ߴ��� ���� ID ���� �ٸ��� �����Ѵ�.
{
}

CCollider::~CCollider()
{
}

void CCollider::finalupdate()
{
	// ������Ʈ�� ��ġ�� ���󰣴�.
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	assert(0 <= m_iCol); // m_iCol �� ������ �Ǵ°� ���� ��Ȳ���� ����.
}

void CCollider::render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	// �浹 �߻��� �� ���� ��ü.
	if (m_iCol)
		ePen = PEN_TYPE::RED;

	// ���� ���� ���� �����ϴ� �ӽ� ��ü.
	SelectGDI p(_dc, ePen);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc
		, (int)(m_vFinalPos.x - m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y - m_vScale.y / 2.f)
		, (int)(m_vFinalPos.x + m_vScale.x / 2.f)
		, (int)(m_vFinalPos.y + m_vScale.y / 2.f));
}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++m_iCol;
	m_pOwner->OnCollisionEnter(_pOther);

}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_iCol;
	m_pOwner->OnCollisionExit(_pOther);
}
