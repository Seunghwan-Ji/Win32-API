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
	// RECT ����ü�� �ּ�, ������ ��Ÿ��(���°�, ��Ʈ ���� ���), �޴��� ����
	// '�������ִ�' �Լ��̱⿡, ������ ����� ��ȯ���� �ʰ� �־��� ����ü �ּ���
	// �������� �����ϴ� ����̴�.
	// ����� ū ����ü�� ��� �������ϸ� ����� �� ����� ����Ѵ�.

	// ������ ������� ������ �ػ� ����.
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd); // DC ����.

	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 }; // �ػ��� ���߾� ��ġ.
	g_obj.m_ptScale = POINT{ 100, 100 }; // ũ�� ����.

	return S_OK;
}

void CCore::progress()
{
	static int callCount = 0;
	++callCount;

	static int iPrevCount = GetTickCount(); // ���� �ð�.
	int iCurCount = GetTickCount(); // ���� �ð�.

	// 1�ʸ��� ����.
	if (iCurCount - iPrevCount > 1000) // 1000 �и��� = 1��
	{
		iPrevCount = iCurCount;
		callCount = 0; // ������� ���� ���� Ȯ���غ��� �� 3��~4�� ������ ���� �����ȴ�.
		// ��, �ʴ� �Լ� ȣ���� �������� ���� �Ǵ°� �� �� �ִ�.
	}

	update();

	render();
}

void CCore::update()
{
	// GetAsyncKeyState: Ư�� Ű�� ���¸� Ȯ���ϴ� �Լ�.
	// Ű�� ���� �ִ� ��������, �����ٰ� ������ �������� �� Ȯ�� ����
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		// 0x8000  : ������ ��Ʈ 1000 0000 0000 0000 �� 16������ ��Ÿ�� ��.
		// & 0x8000: ��ȯ ���� �ֻ��� ��Ʈ(16��° ��Ʈ)�� 1���� Ȯ��.
		// �� ��Ʈ�� �ش� Ű�� ���� ������ �ִ� �������� ��Ÿ��.
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
	// �׸���
	Rectangle(m_hDC, g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
		, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}