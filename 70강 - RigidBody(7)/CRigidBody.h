#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;	 // ��ü ������.

	Vec2    m_vForce;	 // ũ��, ����.
	Vec2	m_vAccel;	 // ���ӵ�.
	Vec2	m_vAccelA;   // �߰� ���ӵ�.
	Vec2    m_vVelocity; // �ӵ�.(ũ��: �ӷ�, ����)

	float	m_fMass;	 // ����.
	float   m_fFricCoef; // ���� ���.
	float   m_fMaxSpeed; // �ִ� �ӷ�.

	// F = M * A
	// V += A * DT

public:
	void finalupdate();

public:
	void AddForce(Vec2 _vF) { m_vForce += _vF; } // ���� �����ϴ� �Լ�.
	void SetMass(float _fMass) { m_fMass = _fMass; } // ������ �����ϴ� �Լ�.
	float GetMass() { return m_fMass; } // ������ ��ȯ�ϴ� �Լ�.
	float GetSpeed() { return m_vVelocity.Length(); } // �ӵ��� ��ȯ�ϴ� �Լ�.
	Vec2 GetVelocity() { return m_vVelocity; }

	void SetVelocity(Vec2 _v) { m_vVelocity = _v; } // �ӵ��� �����ϴ� �Լ�.
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; } // �ӵ��� �����ϴ� �Լ�.
	void SetMaxVelocity(float _speed) { m_fMaxSpeed = _speed; } // �ִ� �ӵ��� �����ϴ� �Լ�.
	void SetAccelALpha(Vec2 _vAccel) { m_vAccelA = _vAccel; }

private:
	void Move(); // �ӵ��� ���� �̵�.

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

