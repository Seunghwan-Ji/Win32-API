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
	// 현재 프로젝트나 실행 파일이 실행된 경로를 멤버 변수 m_szContentPath 에 저장하는 함수.
	GetCurrentDirectory(255, m_szContentPath);

	// <bin 폴더로 접근>
	// 1. 상위 폴더로(Output)
	// 2. path 값 수정: + \\bin\\content\\

	int iLen = (int)wcslen(m_szContentPath); // 경로 문자열 길이 계산.

	for (int i = iLen - 1; 0 <= i; --i) // 역순으로 순회.
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0'; // 마감 문자로 갱신.
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\"); // 문자열 이어붙이기.

	SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath); // 갱신된 경로 출력.
}
