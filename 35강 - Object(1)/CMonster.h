#pragma once
#include "CObject.h"

class CMonster : public CObject
{
private:
	Vec2  m_vCenterPos;	  // �̵� �ݰ��� �߽� ��ǥ.
	float m_fSpeed;		  // �̵� �ӵ�.
	float m_fMaxDistance; // �ִ� �̵� �ݰ�.
	int   m_iDir;		  // �̵� ����.
	int	  m_iHP;          // ���� ü��.

public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _f) { m_fSpeed = _f; }
	void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

public:
	virtual void update();

	CLONE(CMonster);

public:
	CMonster();
	~CMonster();
};