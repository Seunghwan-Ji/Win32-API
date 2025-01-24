#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	// 이전 카운트 값을 현재 값으로 갱신(다음번에 계산을 위해서)
	m_llPrevCount = m_llCurCount;

#ifdef _DEBUG // 디버그 모드에서만 수행되는 전처리기 구문.
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.); // 디버깅중에 시간이 많이 흘러서 DT 값이 커질 때 특정 수치로 제한.
#endif
}

void CTimeMgr::render()
{
	++m_iCallCount;
	m_dAcc += m_dDT; // DT 누적.

	if (m_dAcc >= 1.) // 1초가 흘렀다면.
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		// 배열에 문자열 저장
		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS: %d, DT: %f", m_iFPS, m_dDT);

		// 저장된 문자열 배열을 윈도우 타이틀바에 출력
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
