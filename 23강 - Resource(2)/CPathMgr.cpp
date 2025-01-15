#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{
}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::init()
{
	// ���� ������Ʈ�� ���� ������ ����� ��θ� ��� ���� m_szContentPath �� �����ϴ� �Լ�.
	GetCurrentDirectory(255, m_szContentPath);

	// <bin ������ ����>
	// 1. ���� ������(Output)
	// 2. path �� ����: + \\bin\\content\\

	int iLen = (int)wcslen(m_szContentPath); // ��� ���ڿ� ���� ���.

	for (int i = iLen - 1; 0 <= i; --i) // �������� ��ȸ.
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0'; // ���� ���ڷ� ����.
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\"); // ���ڿ� �̾���̱�.

	SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath); // ���ŵ� ��� ���.
}
