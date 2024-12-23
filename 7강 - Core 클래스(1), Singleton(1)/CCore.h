#pragma once

// 싱글톤 패턴
// 객체의 생성을 1개로 제한.
// 어디서든 쉽게 접근 가능.
class CCore
{
private:
	static CCore* g_pInst; // 데이터 영역에 정적 멤버 변수 할당.

public:
	// 정적 멤버 함수
	static CCore* GetInstance()
	{
		// 최초 호출된 경우
		if (nullptr == g_pInst)
		{
			g_pInst = new CCore;
		}

		return g_pInst;
	}

	// 정적 멤버 변수 메모리 해제 함수
	static void Release()
	{
		if (nullptr != g_pInst)
		{
			delete g_pInst; // 메모리 해제.
			g_pInst = nullptr; // 정적 멤버 함수 호출시, 메모리 할당을 위해 주소값 삭제.
		}
	}

private:
	// 생성자를 private 으로 선언하여, 외부에서 객체를 생성하지 못하게 막음.
	CCore() {}
	~CCore() {}
};

// 정적 멤버 변수의 주소값은 데이터 영역에, 주소로 접근했을 때의 그 값은 힙 영역에 존재한다.