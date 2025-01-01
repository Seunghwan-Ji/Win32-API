#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llFrequency{}
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	QueryPerformanceCounter(&m_llCurCount);
	// GetTickCount 함수보다 더 정밀하게 카운트를 측정하는 함수.

	QueryPerformanceFrequency(&m_llFrequency);
	// 초당 카운트가 얼마나 발생하는지 알아보는 함수.
	// 디버깅을 통해 확인해보면 초당 천만 카운트가 나온다.
}
