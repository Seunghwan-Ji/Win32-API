#pragma once
#include "CObject.h"

class CMissile : public CObject
{
private:
	float m_fTheta; // 이동 방향.(세타)

public:
	void SetDir(float _fTheta) { m_fTheta = _fTheta; }

public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	CMissile();
	~CMissile();
};