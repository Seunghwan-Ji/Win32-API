#pragma once
#include "CScene.h"

class CScene_Start : public CScene
{
private:
	Vec2 m_vForcePos; // 힘을 가할 위치.
	float m_fForceRadius; // 힘 반경.
	float m_fCurRadius; // 현재 반경.
	float m_fForce; // 힘의 세기.
	bool m_bUseForce; // 힘을 사용할 것인지 여부.

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void Enter();
	virtual void Exit();

public:
	void CreateForce();

public:
	CScene_Start();
	~CScene_Start();
};