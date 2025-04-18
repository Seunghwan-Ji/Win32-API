#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CObject.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
{  
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	// 힘의 크기.
	// float fForce = m_vForce.Length();

	// 힘의 방향.
	// m_vForce.Normalize();

	// 가속도의 크기.
	// float m_fAccel = fForce / m_fMass;

	// 가속도.
	m_vAccel = m_vForce / m_fMass; // m_vForce * m_fAccel;

	// 현재 프레임에서의 최종적인 속도.
	m_vVelocity += m_vAccel * fDT;

	// 속도에 따른 이동.
	Move();

	// 힘 초기화.
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// 이동 방향.
	// Vec2 vDir = m_vVelocity;
	// vDir.Normalize();

	// 이동 속력.
	// float fSpeed = m_vVelocity.Length();

	Vec2 vPos = m_pOwner->GetPos();

	vPos += m_vVelocity * fDT;

	m_pOwner->SetPos(vPos);
}