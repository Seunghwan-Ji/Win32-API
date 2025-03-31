#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;	 // 강체 소유자.

	Vec2    m_vForce;	 // 크기, 방향.
	Vec2	m_vAccel;	 // 가속도.
	Vec2	m_vAccelA;   // 추가 가속도.
	Vec2    m_vVelocity; // 속도.(크기: 속력, 방향)

	float	m_fMass;	 // 질량.
	float   m_fFricCoef; // 마찰 계수.
	float   m_fMaxSpeed; // 최대 속력.

	// F = M * A
	// V += A * DT

public:
	void finalupdate();

public:
	void AddForce(Vec2 _vF) { m_vForce += _vF; } // 힘을 누적하는 함수.
	void SetMass(float _fMass) { m_fMass = _fMass; } // 질량을 설정하는 함수.
	float GetMass() { return m_fMass; } // 질량을 반환하는 함수.
	float GetSpeed() { return m_vVelocity.Length(); } // 속도를 반환하는 함수.
	Vec2 GetVelocity() { return m_vVelocity; }

	void SetVelocity(Vec2 _v) { m_vVelocity = _v; } // 속도를 설정하는 함수.
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; } // 속도를 누적하는 함수.
	void SetMaxVelocity(float _speed) { m_fMaxSpeed = _speed; } // 최대 속도를 설정하는 함수.
	void SetAccelALpha(Vec2 _vAccel) { m_vAccelA = _vAccel; }

private:
	void Move(); // 속도에 따른 이동.

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

