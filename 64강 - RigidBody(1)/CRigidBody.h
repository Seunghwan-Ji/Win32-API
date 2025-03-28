#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;

	Vec2    m_vForce;	 // 크기, 방향.
	Vec2	m_vAccel;	 // 가속도.
	Vec2    m_vVelocity; // 속도.(크기: 속력, 방향)
	float	m_fMass;	 // 질량.

	// F = M * A
	// V += A * DT

public:
	void finalupdate();

public:
	void AddForce(Vec2 _vF) { m_vForce += _vF; } // 힘을 누적하는 함수.
	void SetMass(float _fMass) { m_fMass = _fMass; } // 질량을 설정하는 함수.

	float GetMass() { return m_fMass; }

private:
	void Move();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

