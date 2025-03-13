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
	// ���� ũ��.
	// float fForce = m_vForce.Length();

	// ���� ����.
	// m_vForce.Normalize();

	// ���ӵ��� ũ��.
	// float m_fAccel = fForce / m_fMass;

	// ���ӵ�.
	m_vAccel = m_vForce / m_fMass; // m_vForce * m_fAccel;

	// ���� �����ӿ����� �������� �ӵ�.
	m_vVelocity += m_vAccel * fDT;

	// �ӵ��� ���� �̵�.
	Move();

	// �� �ʱ�ȭ.
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	// �̵� ����.
	// Vec2 vDir = m_vVelocity;
	// vDir.Normalize();

	// �̵� �ӷ�.
	// float fSpeed = m_vVelocity.Length();

	Vec2 vPos = m_pOwner->GetPos();

	vPos += m_vVelocity * fDT;

	m_pOwner->SetPos(vPos);
}