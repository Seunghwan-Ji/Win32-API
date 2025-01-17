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

	// ���� ����ϴ� GDI object
	HBRUSH  m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN    m_arrPen[(UINT)PEN_TYPE::END];

public:
	int Init(HWND _hWnd, POINT _ptResolution); // ������ �ʱ�ȭ �Լ�.
	void progress(); // �񵿱�� ���α׷����� �޽����� �߻����� �ʴ� ���� ������ �Լ�.

private:
	void CreateBrushPen();

public:
	HWND GetMainHwnd() { return m_hWnd; }			 // ���� ������ �ڵ� ��ȯ �Լ�.
	HDC GetMainDC() { return m_hDC; }				 // ���� ������ DC ��ȯ �Լ�.
	POINT GetResolution() { return m_ptResolution; } // �ػ� ��ȯ �Լ�.
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};