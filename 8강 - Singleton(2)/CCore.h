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

public:
	int Init(HWND _hWnd, POINT _ptResolution); // ������ �ʱ�ȭ �Լ�.
	void progress(); // �񵿱�� ���α׷����� �޽����� �߻����� �ʴ� ���� ������ �Լ�.

private:
	CCore();
	~CCore();
};

//class CCore
//{
//public:
//	static CCore* GetInst()
//	{
//		static CCore core; // ������ ������ ���� ��ü ����.
//		// �� �̱��� ���� ����� �����ϴ�.
//		// ������ �����̶� ����ڰ� �޸𸮸� �������� �������� �ʾƵ� ������,
//		// �ݴ�� ����ڰ� ���� �� �������� ���ϴ� ������ �ִ�.
//		
//		return &core; // ��ü�� �ּ� ����.
//	}
//
//private:
//	CCore();
//	~CCore();
//};