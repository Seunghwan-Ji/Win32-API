#pragma once

// 싱글톤 패턴
// 객체의 생성을 1개로 제한.
// 어디서든 쉽게 접근 가능.

class CCore
{
	SINGLE(CCore); // define 헤더 파일의 매크로 활용.

private:
	HWND  m_hWnd;	      // 메인 윈도우 핸들.
	POINT m_ptResolution; // 메인 윈도우 해상도.
	HDC   m_hDC;		  // 메인 윈도우에 Draw 할 DC.

public:
	int Init(HWND _hWnd, POINT _ptResolution); // 윈도우 초기화 함수.
	void progress(); // 비동기식 프로그램에서 메시지가 발생하지 않는 동안 실행할 함수.

private:
	void update(); // 물체들의 변경점을 체크하는 함수.
	void render(); // 물체들을 그리는 함수.(렌더링)
	CCore();
	~CCore();
};