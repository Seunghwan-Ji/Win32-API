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
	// 멤버 m_llFrequency 는 초당 셀 수 있는 카운트 값이 저장되어있다.
	// 예를들어 초당 100 카운트를 셀 수 있다고 가정할 때,
	// 이전 프레임과 현재 프레임의 카운팅 값 차이가 50이라면 0.5초가 흘렀다는 것을 알 수 있다.
	// QuadPart 는 정수값이다. 따라서 나눈 결과가 0이 나오는 것을 방지하기 위해
	// 실수 자료형으로 형변환한다.

	// 이전 카운트 값을 현재 값으로 갱신(다음번에 계산을 위해서)
	m_llPrevCount = m_llCurCount;

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
