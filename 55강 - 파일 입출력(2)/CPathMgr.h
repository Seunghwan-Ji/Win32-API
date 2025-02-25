#pragma once

class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wchar_t m_szContentPath[256]; // content 폴더 경로.
	wchar_t m_szRelativePath[256]; // 파일 상대 경로 문자열.

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; } // 경로 훼손 방지로 상수화해서 반환.
	wstring GetRelativePath(const wchar_t* _filePath); // 상대 경로 반환 함수.
};