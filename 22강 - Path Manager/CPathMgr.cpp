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
	GetCurrentDirectory(255, m_szContentPath); // 현재 프로젝트나 실행 파일이 실행된 경로 반환 함수.
	// 매개변수: 버퍼 길이, 배열의 주소.

// SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath); // 경로 출력.
// 빌드된 실행 파일에서 실행시, Output 폴더 내부 경로로 출력된다.
// 부모 폴더인 Output 폴더로 이동 후, bin 폴더로 상대적으로 접근할 수 있지만,
// 비주얼스튜디오 환경에서 실행시, 솔루션 파일이 있는 경로가 출력된다.
// 따라서 비주얼스튜디오 환경에서 실행시엔, bin 폴더로 상대적으로 접근할 수 없다.

// 이 문제를 해결하기 위해서는 비주얼스튜디오 환경에서 실행시에도, bin 폴더로
// 접근할 수 있도록 '디버깅 작업 디렉터리' 를 수정해줘야 한다.

// 프로젝트 우클릭 -> 속성 -> 디버깅 -> 왼쪽 상단 구성 -> 모든 구성 선택 ->
// 작업 디렉터리 수정 -> $(SolutionDir)Output\bin\ -> 적용, 확인


// <bin 폴더로 접근>
// 1. 상위 폴더로(Output)
// 2. path 값 수정: + \\bin\\content\\

	int iLen = wcslen(m_szContentPath); // 경로 문자열 길이 계산.

	for (int i = iLen - 1; 0 <= i; --i) // 역순으로 순회.
		// 마지막 인덱스는 문자열 길이 - 1.
	{
		if ('\\' == m_szContentPath[i])
			// '\\'는 백슬래시 문자를 이스케이프 처리한 것으로, 실제로는 백슬래시 하나를 의미.
		{
			m_szContentPath[i] = '\0'; // 마감 문자로 갱신.
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\"); // 문자열 이어붙이기.

	SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath); // 갱신된 경로 출력.
}
