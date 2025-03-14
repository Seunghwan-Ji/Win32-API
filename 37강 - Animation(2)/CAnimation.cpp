#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::update()
{
}

void CAnimation::render(HDC _dc)
{
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep
	, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};

	// 프레임 벡터 각 요소에 한 프레임의 정보 구조체 저장.
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * i;

		m_vecFrm.push_back(frm);
	}
}
