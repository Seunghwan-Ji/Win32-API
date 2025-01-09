#pragma once

// �̱��� ����
// ��ü�� ������ 1���� ����.
// ��𼭵� ���� ���� ����.

class CCore
{
	SINGLE(CCore); // define ��� ������ ��ũ�� Ȱ��.

private:
	HWND	m_hWnd;			// ���� ������ �ڵ�.
	POINT	m_ptResolution; // ���� ������ �ػ�.
	HDC		m_hDC;			// ���� �����쿡 Draw �� DC.

	HBITMAP m_hBit;			// ��Ʈ�� �ڵ�.(�޸𸮿� ������ �̹��� �Ǵ� �׷��� �����͸� �ĺ�.)
	HDC		m_memDC;		// �޸� DC �ڵ�.(�޸� �������� �׸��� �۾��� �����ϱ� ���� ���.)

public:
	int Init(HWND _hWnd, POINT _ptResolution); // ������ �ʱ�ȭ �Լ�.
	void progress(); // �񵿱�� ���α׷����� �޽����� �߻����� �ʴ� ���� ������ �Լ�.

private:
	void update(); // ��ü���� �������� üũ�ϴ� �Լ�.
	void render(); // ��ü���� �׸��� �Լ�.(������)

public:
	HWND GetMainHwnd() { return m_hWnd; } // ���� ������ �ڵ� ��ȯ �Լ�.
	POINT GetResolution() { return m_ptResolution; } // �ػ� ��ȯ �Լ�.
};