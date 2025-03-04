#pragma once
#include "CObject.h"

class AI;

class CMonster : public CObject
{
private:
	float m_fSpeed;		  // 이동 속도.
	int	  m_iHP;          // 몬스터 체력.

	AI*   m_pAI;

public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _f) { m_fSpeed = _f; }

	void SetAI(AI* _AI); // AI 지정.

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

public:
	virtual void update();

	CLONE(CMonster);

public:
	CMonster();
	~CMonster();
};