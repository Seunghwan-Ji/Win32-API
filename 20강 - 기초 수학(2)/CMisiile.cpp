#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fTheta(PI / 2.f) // 2분의 파이 = 90도.
	, m_vDir(Vec2(1.f, 1.f)) // 45도(직각이등변삼각형 성질)
{
	m_vDir.Normalize(); // 벡터 정규화 진행.
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	// vPos.x += 600.f * cosf(m_fTheta) * fDT;
	// vPos.y += 600.f * sinf(m_fTheta) * fDT;

	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	// 원 그리는 함수.
	Ellipse(_dc, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f));
}
