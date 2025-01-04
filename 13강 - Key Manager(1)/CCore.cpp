#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CObject g_obj;

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

	// 해상도의 정중앙 위치.
	g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));

	// 오브젝트의 크기 설정.
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	update();
	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos(); // 오브젝트의 현재 좌표 읽어오기.

	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		vPos.x -= 200.f * fDT; // 초당 200 픽셀 만큼의 이동속도.
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		vPos.x += 200.f * fDT;
	}

	g_obj.SetPos(vPos); // 오브젝트의 좌표 갱신.
}

void CCore::render()
{
	// 화면 Clear.(두번째 비트맵에)
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// 그리기(두번째 비트맵에)
	Rectangle(m_memDC, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f));

	// 메인 윈도우 비트맵으로 복사.
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);
}