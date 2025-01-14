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
	GetCurrentDirectory(255, m_szContentPath); // ���� ������Ʈ�� ���� ������ ����� ��� ��ȯ �Լ�.
	// �Ű�����: ���� ����, �迭�� �ּ�.

// SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath); // ��� ���.
// ����� ���� ���Ͽ��� �����, Output ���� ���� ��η� ��µȴ�.
// �θ� ������ Output ������ �̵� ��, bin ������ ��������� ������ �� ������,
// ���־�Ʃ��� ȯ�濡�� �����, �ַ�� ������ �ִ� ��ΰ� ��µȴ�.
// ���� ���־�Ʃ��� ȯ�濡�� ����ÿ�, bin ������ ��������� ������ �� ����.

// �� ������ �ذ��ϱ� ���ؼ��� ���־�Ʃ��� ȯ�濡�� ����ÿ���, bin ������
// ������ �� �ֵ��� '����� �۾� ���͸�' �� ��������� �Ѵ�.

// ������Ʈ ��Ŭ�� -> �Ӽ� -> ����� -> ���� ��� ���� -> ��� ���� ���� ->
// �۾� ���͸� ���� -> $(SolutionDir)Output\bin\ -> ����, Ȯ��


// <bin ������ ����>
// 1. ���� ������(Output)
// 2. path �� ����: + \\bin\\content\\

	int iLen = wcslen(m_szContentPath); // ��� ���ڿ� ���� ���.

	for (int i = iLen - 1; 0 <= i; --i) // �������� ��ȸ.
		// ������ �ε����� ���ڿ� ���� - 1.
	{
		if ('\\' == m_szContentPath[i])
			// '\\'�� �齽���� ���ڸ� �̽������� ó���� ������, �����δ� �齽���� �ϳ��� �ǹ�.
		{
			m_szContentPath[i] = '\0'; // ���� ���ڷ� ����.
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\"); // ���ڿ� �̾���̱�.

	SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath); // ���ŵ� ��� ���.
}
