#include "pch.h"
#include "CCore.h"

CCore::CCore()
{
}

CCore::~CCore()
{
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정.

	return S_OK;

	// 윈도우 기능 내부의 전처리기

	// #define S_OK                                   ((HRESULT)0L) :
	// S_OK = 0을 의미.

	// #define S_FALSE                                ((HRESULT)1L) :
	// S_FALSE = 1을 의미.

	// #define FAILED(hr) (((HRESULT)(hr)) < 0) :
	// 'hr' 이 음수면 true 이다.

	// #define E_FAIL                           _HRESULT_TYPEDEF_(0x80004005L) :
	// E_FAIL = 음수를 의미.

	// 윈도우에서 제공하는 대부분의 함수 결과값은 'HRESULT' 라는 타입이다.
	// 'HRESULT' 는 long 자료형을 타입 재정의 한 것이다.
}

void CCore::progress()
{
}
