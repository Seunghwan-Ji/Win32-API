#include "pch.h"
#include "CCore.h"

CCore::CCore()
{
}

CCore::~CCore()
{
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����.

	return S_OK;

	// ������ ��� ������ ��ó����

	// #define S_OK                                   ((HRESULT)0L) :
	// S_OK = 0�� �ǹ�.

	// #define S_FALSE                                ((HRESULT)1L) :
	// S_FALSE = 1�� �ǹ�.

	// #define FAILED(hr) (((HRESULT)(hr)) < 0) :
	// 'hr' �� ������ true �̴�.

	// #define E_FAIL                           _HRESULT_TYPEDEF_(0x80004005L) :
	// E_FAIL = ������ �ǹ�.

	// �����쿡�� �����ϴ� ��κ��� �Լ� ������� 'HRESULT' ��� Ÿ���̴�.
	// 'HRESULT' �� long �ڷ����� Ÿ�� ������ �� ���̴�.
}

void CCore::progress()
{
}
