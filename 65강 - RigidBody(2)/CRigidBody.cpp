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
	// ���ӵ�.
	m_vAccel = m_vForce / m_fMass; // m_vForce * m_fAccel;

	// ���� �����ӿ����� �������� �ӵ�.
	m_vVelocity += m_vAccel * fDT;

	// �����¿� ���� �ݴ� ���������� ���ӵ�.
	if (!m_vVelocity.IsZero()) // �ӵ��� 0�� �ƴ� ���� �������� �����Ѵ�.
	{
		Vec2 vFricDir = -m_vVelocity; // �������� ������ �ӵ��� �ݴ� ����.
		vFricDir.Normalize(); // �������� ������ ����ȭ.

		Vec2 vFriction = vFricDir * m_fFricCoef * fDT; // �������� ũ��.
		if (m_vVelocity.Length() <= vFriction.Length()) // �������� ũ�Ⱑ �ӵ��� ũ�⺸�� ũ�ų� ������ �ӵ��� 0���� �����.
		{
			// ���� ���ӵ��� ���� �ӵ����� ũ�� �ӵ��� 0���� �����.
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			// ���� ���ӵ��� ���� �ӵ����� ������ �ӵ��� ���� ���ӵ��� ���Ѵ�.
			m_vVelocity += vFriction;
		}
	}

	// �ӵ� ���� �˻�.
	if (m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
	}

	// �ӵ��� ���� �̵�.
	Move();

	// �� �ʱ�ȭ.
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	Vec2 vPos = m_pOwner->GetPos(); // ���� ��ġ.

	vPos += m_vVelocity * fDT; // ���� ��ġ�� �ӵ��� ���� ���ο� ��ġ�� ���Ѵ�.

	m_pOwner->SetPos(vPos); // ���ο� ��ġ�� �̵�.
}