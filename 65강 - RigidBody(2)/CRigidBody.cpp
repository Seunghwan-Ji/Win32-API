#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CObject.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFricCoef(100.f)
	, m_fMaxSpeed(200.f)
{  
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	// 가속도.
	m_vAccel = m_vForce / m_fMass; // m_vForce * m_fAccel;

	// 현재 프레임에서의 최종적인 속도.
	m_vVelocity += m_vAccel * fDT;

	// 마찰력에 의한 반대 방향으로의 가속도.
	if (!m_vVelocity.IsZero()) // 속도가 0이 아닐 때만 마찰력을 적용한다.
	{
		Vec2 vFricDir = -m_vVelocity; // 마찰력의 방향은 속도의 반대 방향.
		vFricDir.Normalize(); // 마찰력의 방향을 정규화.

		Vec2 vFriction = vFricDir * m_fFricCoef * fDT; // 마찰력의 크기.
		if (m_vVelocity.Length() <= vFriction.Length()) // 마찰력의 크기가 속도의 크기보다 크거나 같으면 속도를 0으로 만든다.
		{
			// 마찰 가속도가 본래 속도보다 크면 속도를 0으로 만든다.
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			// 마찰 가속도가 본래 속도보다 작으면 속도에 마찰 가속도를 더한다.
			m_vVelocity += vFriction;
		}
	}

	// 속도 제한 검사.
	if (m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
	}

	// 속도에 따른 이동.
	Move();

	// 힘 초기화.
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	Vec2 vPos = m_pOwner->GetPos(); // 현재 위치.

	vPos += m_vVelocity * fDT; // 현재 위치에 속도를 더해 새로운 위치를 구한다.

	m_pOwner->SetPos(vPos); // 새로운 위치로 이동.
}