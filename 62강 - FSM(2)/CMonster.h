#pragma once
#include "CObject.h"

class AI;

class CMonster : public CObject
{
private:
	float m_fSpeed;		  // �̵� �ӵ�.
	int	  m_iHP;          // ���� ü��.

	AI*   m_pAI;

public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _f) { m_fSpeed = _f; }

	void SetAI(AI* _AI); // AI ����.

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

public:
	virtual void update();

	CLONE(CMonster);

public:
	CMonster();
	~CMonster();
};