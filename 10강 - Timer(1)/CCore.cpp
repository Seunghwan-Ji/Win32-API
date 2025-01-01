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
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC); // DC ����.
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
	static int callCount = 0;
	++callCount;

	/*if (60 >= callCount)
	{
		update();
		render();
		++callCount;
	}*/

	static int iPrevCount = GetTickCount(); // ���� �ð�.
	int iCurCount = GetTickCount(); // ���� �ð�.

	// 1�ʸ��� ����.
	if (iCurCount - iPrevCount > 1000) // 1000 �и��� = 1��
	{
		iPrevCount = iCurCount;
		callCount = 0;
	}

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
		vPos.x -= 0.01f;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 0.01f;
	}

	g_obj.SetPos(vPos); // ������Ʈ�� ��ǥ ����.
}

void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// �׸���
	Rectangle(m_hDC, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f));
}