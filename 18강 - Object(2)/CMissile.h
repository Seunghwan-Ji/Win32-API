#pragma once
#include "CObject.h"

class CMissile : public CObject
{
private:
	float m_fDir; // 위 아래 방향.

public:
	void SetDir(bool _up)
	{
		if (_up)
			m_fDir = -1.f;
		else
			m_fDir = 1.f;
	}

public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	CMissile();
	~CMissile();
};