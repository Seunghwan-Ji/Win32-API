#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC); // DC 해제.

	// 비트맵 핸들과 메모리 DC 해제.
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd; // 윈도우 핸들.
	m_ptResolution = _ptResolution; // 윈도우 해상도.

	// 해상도에 맞게 윈도우 크기 조정.
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	// 윈도우 창의 타이틀바, 메뉴바 등을 제외한 사이즈로 조정해주는 함수.

	// 조정된 사이즈로 윈도우 해상도 설정.
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd); // DC 생성.

	// 이중 버퍼링 용도의 비트맵과 DC 를 만든다.(이중 렌더링)
	// 윈도우 해상도 크기만큼 비트맵 생성.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	// 생성한 비트맵에 그리기 작업을 할 DC 생성.
	m_memDC = CreateCompatibleDC(m_hDC);

	// DC 가 그릴 목적지를 생성한 비트맵으로 지정해준다.
	HBITMAP hOldBIt = (HBITMAP)SelectObject(m_memDC, m_hBit);

	// DC 가 갖고 있던 기본 비트맵 제거.
	DeleteObject(hOldBIt);

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();

	return S_OK;
}

void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();

	// =========
	// Rendering
	// =========
	// 화면 Clear.(두번째 비트맵에)
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	// 메인 윈도우 비트맵으로 복사.
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);
}