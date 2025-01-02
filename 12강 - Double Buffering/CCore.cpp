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
	// RECT ����ü���� PRECT �� LPRECT �� RECT ����ü�� �������� RECT* �� �ǹ��Ѵ�.

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
	// DC �� ������ ��, �⺻������ 1�ȼ� ũ���� ��Ʈ���� ����Ű�� �ִ�.

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

	update();
	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos(); // ������Ʈ�� ���� ��ǥ �о����.

	// GetAsyncKeyState: Ư�� Ű�� ���¸� Ȯ���ϴ� �Լ�.
	// Ű�� ���� �ִ� ��������, �����ٰ� ������ �������� �� Ȯ�� ����
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 200.f * fDT; // �ʴ� 200 �ȼ� ��ŭ�� �̵��ӵ�.
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 200.f * fDT;
	}

	g_obj.SetPos(vPos); // ������Ʈ�� ��ǥ ����.
}

void CCore::render()
{
	// ȭ�� Clear.(�ι�° ��Ʈ�ʿ�)
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	// ������Ʈ�� �̵��� �� �ܻ��� �����Ƿ�, �ػ� ũ�⸸ŭ ��ȭ���� �׷����� ����� ä���Ѵ�.
	// ��, ������ �׵θ� ����� ��ġ�� �ʰ� 1�ȼ� �� �������� ���δ�.

	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// �׸���(�ι�° ��Ʈ�ʿ�)
	Rectangle(m_memDC, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f));

	// ���� ������ ��Ʈ������ ����.
	// ��Ʈ���� ������ DC �κ��� ������ ��Ʈ���� ������ DC �� ��Ʈ���� ��� �ȼ� �޸𸮸� �ű��.
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);
	// ������ ��Ʈ���� ��ü �ػ� ũ�⿡ �ι�° ��Ʈ���� �»�� 0, 0 ����
	// ��� �ȼ� �޸𸮸� ����(SRCCOPY)��Ų��.
}