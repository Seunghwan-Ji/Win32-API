#include "pch.h"
#include "CAnimation.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::update()
{
	if (m_bFinish)
		return;

	// 누적 시간을 갱신.
	m_fAccTime += fDT;

	// 현재 애니메이션 프레임이 화면에 보여질 지속 시간이 초과되었는지를 확인.
	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		// 다음 프레임으로 넘어감.
		++m_iCurFrm;

		// 현재 프레임 인덱스가 애니메이션 프레임 벡터 크기를 초과했으면, 애니메이션이 끝났다고 판단.
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
		}

		// 다음 프레임을 표시하기 위해 누적 시간에서 현재 프레임의 지속 시간을 차감.
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
		// 이렇게 해야 남은 경과 시간을 유지하면서 자연스럽게 다음 프레임의 타이밍을 맞출 수 있다.
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;

	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f) // 그릴곳의 좌상단 x좌표.
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f) // 그릴곳의 좌상단 y좌표.
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x) // 그릴곳의 좌상단으로 부터 너비.
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y) // 그릴곳의 좌상단으로 부터 높이.
		, m_pTex->GetDC()					  // 텍스쳐의 DC.
		, (int)(m_vecFrm[m_iCurFrm].vLT.x)    // 자를곳의 좌상단 x좌표.
		, (int)(m_vecFrm[m_iCurFrm].vLT.y)    // 자를곳의 좌상단 y좌표.
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x) // 자를곳의 좌상단으로 부터 너비.
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y) // 자를곳의 좌상단으로 부터 높이.
		, RGB(255, 0, 255)                    // 투명 처리할 색상.
	);
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
