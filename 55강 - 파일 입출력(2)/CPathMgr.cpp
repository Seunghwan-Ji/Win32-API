#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::init()
{
	// ���� ������Ʈ�� ���� ������ ����� ��θ� ��� ���� m_szContentPath �� �����ϴ� �Լ�.
	GetCurrentDirectory(256, m_szContentPath);

	// <bin ������ ����>
	// 1. ���� ������(Output)
	// 2. path �� ����: + \\bin\\content\\

	int iLen = (int)wcslen(m_szContentPath); // ��� ���ڿ� ���� ���.

	// Output ��� ������ ����.
	for (int i = iLen - 1; 0 <= i; --i) // �������� ��ȸ.
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0'; // ���� ���ڷ� ����.
			break;
		}
	}

	wcscat_s(m_szContentPath, 256, L"\\bin\\content\\"); // ���ڿ� �̾���̱�.(content ��α��� �ϼ�.)

	SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath); // ���ŵ� ��� ���.
}

wstring CPathMgr::GetRelativePath(const wchar_t* _filePath)
{
	// ���� ���.(��ü ���)
	wstring strFilePath = _filePath;

	size_t iContentPathLen = wcslen(m_szContentPath); // content ���� ������ ��� ����.
	size_t iFullPathLen = strFilePath.length(); // ��ü ��� ����.

	// ��� ��� ����.(content ~ ������)
	// iContentPathLen ��ġ���� iFullPathLen - iContentPathLen ���̸�ŭ�� �κ� ���ڿ��� ����.
	wstring strRelativePath = strFilePath.substr(iContentPathLen, iFullPathLen - iContentPathLen);

	return strRelativePath;
}
