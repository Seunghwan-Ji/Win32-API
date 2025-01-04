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
	ReleaseDC(m_hWnd, m_hDC); // DC ����.

	// ��Ʈ�� �ڵ�� �޸� DC ����.
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd; // ������ �ڵ�.
	m_ptResolution = _ptResolution; // ������ �ػ�.

	// �ػ󵵿� �°� ������ ũ�� ����.
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	// ������ â�� Ÿ��Ʋ��, �޴��� ���� ������ ������� �������ִ� �Լ�.

	// ������ ������� ������ �ػ� ����.
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd); // DC ����.

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC �� �����.(���� ������)
	// ������ �ػ� ũ�⸸ŭ ��Ʈ�� ����.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	// ������ ��Ʈ�ʿ� �׸��� �۾��� �� DC ����.
	m_memDC = CreateCompatibleDC(m_hDC);

	// DC �� �׸� �������� ������ ��Ʈ������ �������ش�.
	HBITMAP hOldBIt = (HBITMAP)SelectObject(m_memDC, m_hBit);

	// DC �� ���� �ִ� �⺻ ��Ʈ�� ����.
	DeleteObject(hOldBIt);

	// Manager �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();

	// �ػ��� ���߾� ��ġ.
	g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));

	// ������Ʈ�� ũ�� ����.
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
	Vec2 vPos = g_obj.GetPos(); // ������Ʈ�� ���� ��ǥ �о����.

	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		vPos.x -= 200.f * fDT; // �ʴ� 200 �ȼ� ��ŭ�� �̵��ӵ�.
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		vPos.x += 200.f * fDT;
	}

	g_obj.SetPos(vPos); // ������Ʈ�� ��ǥ ����.
}

void CCore::render()
{
	// ȭ�� Clear.(�ι�° ��Ʈ�ʿ�)
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// �׸���(�ι�° ��Ʈ�ʿ�)
	Rectangle(m_memDC, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f));

	// ���� ������ ��Ʈ������ ����.
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);
}