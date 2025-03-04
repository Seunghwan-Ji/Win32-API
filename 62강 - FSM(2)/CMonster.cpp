#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "AI.h"

CMonster::CMonster()
	: m_fSpeed(100.f)
	, m_iHP(5)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}

void CMonster::update()
{
	m_pAI->update();
}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_iHP -= 1;

		if (m_iHP <= 0)
		{
			DeleteObject(this);
		}
	}
}