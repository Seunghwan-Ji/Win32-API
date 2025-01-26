#pragma once
#include "CObject.h"

class CMissile : public CObject
{
private:
	float m_fTheta; // 이동 방향.(세타, 라디안 지정 방식)
	Vec2 m_vDir; // 이동 방향.(벡터 지정 방식)

public:
	void SetDir(float _fTheta) { m_fTheta = _fTheta; }
	void SetDir(Vec2 _vDir)
	{
		m_vDir = _vDir;
		m_vDir.Normalize();
	}

public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

	CLONE(CMissile);

public:
	CMissile();
	~CMissile();
};