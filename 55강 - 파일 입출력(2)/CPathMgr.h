#pragma once

class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wchar_t m_szContentPath[256]; // content ���� ���.
	wchar_t m_szRelativePath[256]; // ���� ��� ��� ���ڿ�.

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; } // ��� �Ѽ� ������ ���ȭ�ؼ� ��ȯ.
	wstring GetRelativePath(const wchar_t* _filePath); // ��� ��� ��ȯ �Լ�.
};