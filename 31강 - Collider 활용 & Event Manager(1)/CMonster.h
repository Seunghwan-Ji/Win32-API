#pragma once
#include "CObject.h"

class CMonster : public CObject
{
private:
	Vec2  m_vCenterPos;	  // 이동 반경의 중심 좌표.
	float m_fSpeed;		  // 이동 속도.
	float m_fMaxDistance; // 최대 이동 반경.
	int   m_iDir;		  // 이동 방향.

public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _f) { m_fSpeed = _f; }
	void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

public:
	virtual void OnCollision(CCollider* _pOther);

public:
	virtual void update();

public:
	CMonster();
	~CMonster();
};