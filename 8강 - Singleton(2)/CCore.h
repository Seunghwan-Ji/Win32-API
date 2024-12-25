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

public:
	int Init(HWND _hWnd, POINT _ptResolution); // 윈도우 초기화 함수.
	void progress(); // 비동기식 프로그램에서 메시지가 발생하지 않는 동안 실행할 함수.

private:
	CCore();
	~CCore();
};

//class CCore
//{
//public:
//	static CCore* GetInst()
//	{
//		static CCore core; // 데이터 영역에 정적 객체 생성.
//		// 이 싱글톤 패턴 방식은 간결하다.
//		// 데이터 영역이라서 사용자가 메모리를 수동으로 해제하지 않아도 되지만,
//		// 반대로 사용자가 원할 때 해제하지 못하는 단점이 있다.
//		
//		return &core; // 객체의 주소 전달.
//	}
//
//private:
//	CCore();
//	~CCore();
//};