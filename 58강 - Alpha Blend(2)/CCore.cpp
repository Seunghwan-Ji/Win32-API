#include "pch.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CTexture.h"
#include "CResMgr.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC); // DC 해제.

	// 펜 삭제.
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
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

	// 이중 버퍼링 용도의 텍스처 한 장을 만든다.
	m_pMemTex = CResMgr::GetInst()->CreateTexture(
		L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	// 자주 사용할 펜 및 브러쉬 생성.
	CreateBrushPen();

	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSceneMgr::GetInst()->init();

	return S_OK;
}

void CCore::progress()
{
	// ==============
	// Manager Update
	// ==============
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();

	// ============
	// Scene Update
	// ============
	CSceneMgr::GetInst()->update();

	// 충돌 체크.
	CCollisionMgr::GetInst()->update();

	// UI 이벤트 체크.
	CUIMgr::GetInst()->update();

	// =========
	// Rendering
	// =========
	// 화면 Clear.(두번째 비트맵에)
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	// 메인 윈도우 비트맵으로 복사.
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render(); // 프레임, DT 출력.

	// ===============
	// 이벤트 지연 처리
	// ===============
	CEventMgr::GetInst()->update();
}

void CCore::CreateBrushPen()
{
	// hollow brush.
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// red, green, blue pen.
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));


}