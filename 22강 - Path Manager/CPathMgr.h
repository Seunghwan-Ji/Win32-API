#pragma once

class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wchar_t m_szContentPath[255]; // 윈도우에서 경로의 글자 수 제한은 255자이다.

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; } // 경로 훼손 방지로 상수화해서 반환.
};