#pragma once

// �̱��� ����
// ��ü�� ������ 1���� ����.
// ��𼭵� ���� ���� ����.

class CCore
{
	SINGLE(CCore); // define ��� ������ ��ũ�� Ȱ��.

private:
	HWND  m_hWnd;	      // ���� ������ �ڵ�.
	POINT m_ptResolution; // ���� ������ �ػ�.
	HDC   m_hDC;		  // ���� �����쿡 Draw �� DC.

public:
	int Init(HWND _hWnd, POINT _ptResolution); // ������ �ʱ�ȭ �Լ�.
	void progress(); // �񵿱�� ���α׷����� �޽����� �߻����� �ʴ� ���� ������ �Լ�.

private:
	void update(); // ��ü���� �������� üũ�ϴ� �Լ�.
	void render(); // ��ü���� �׸��� �Լ�.(������)
	CCore();
	~CCore();
};