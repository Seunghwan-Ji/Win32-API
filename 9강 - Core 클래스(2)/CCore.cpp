#include "pch.h"
#include "CCore.h"
#include "CObject.h"

CObject g_obj;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC); // DC 해제.
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd; // 윈도우 핸들.
	m_ptResolution = _ptResolution; // 윈도우 해상도.

	// 해상도에 맞게 윈도우 크기 조정.
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	// RECT 구조체에서 PRECT 와 LPRECT 는 RECT 구조체의 포인터인 RECT* 를 의미한다.

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	// 윈도우 창의 타이틀바, 메뉴바 등을 제외한 사이즈로 조정해주는 함수.
	// RECT 구조체의 주소, 윈도우 스타일(상태값, 비트 연산 방식), 메뉴바 유무
	// '조정해주는' 함수이기에, 조정된 결과를 반환하지 않고 넣어준 구조체 주소의
	// 원본값을 수정하는 방식이다.
	// 사이즈가 큰 구조체의 경우 성능저하를 대비해 이 방식을 사용한다.

	// 조정된 사이즈로 윈도우 해상도 설정.
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd); // DC 생성.

	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 }; // 해상도의 정중앙 위치.
	g_obj.m_ptScale = POINT{ 100, 100 }; // 크기 설정.

	return S_OK;
}

void CCore::progress()
{
	static int callCount = 0;
	++callCount;

	static int iPrevCount = GetTickCount(); // 이전 시간.
	int iCurCount = GetTickCount(); // 현재 시간.

	// 1초마다 갱신.
	if (iCurCount - iPrevCount > 1000) // 1000 밀리초 = 1초
	{
		iPrevCount = iCurCount;
		callCount = 0; // 디버깅을 통해 값을 확인해보면 약 3만~4만 사이의 값이 측정된다.
		// 즉, 초당 함수 호출이 이정도로 많이 되는걸 알 수 있다.
	}

	update();

	render();
}

void CCore::update()
{
	// GetAsyncKeyState: 특정 키의 상태를 확인하는 함수.
	// 키가 눌려 있는 상태인지, 눌렀다가 떼어진 상태인지 등 확인 가능
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		// 0x8000  : 이진수 비트 1000 0000 0000 0000 를 16진수로 나타낸 값.
		// & 0x8000: 반환 값의 최상위 비트(16번째 비트)가 1인지 확인.
		// 이 비트는 해당 키가 현재 눌려져 있는 상태인지 나타냄.
	{
		g_obj.m_ptPos.x -= 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 1;
	}
}

void CCore::render()
{
	// 그리기
	Rectangle(m_hDC, g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
		, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}