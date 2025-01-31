#pragma once
#include "CScene.h"
// CScene_Start 클래스가 CScene 클래스를 상속하고 있기 때문에 반드시
// CScene_Start.h 에서도 포함되어야 한다.

// 이유:
// 상속 관계에서 컴파일러는 부모 클래스의 정의가 필요하다.
// 상속 구조를 해석하려면 컴파일러가 CScene 의 멤버 변수와 함수 목록을 알아야 한다.
// 그렇기 때문에 헤더에서 상속을 선언할 때 부모 클래스의 정의가 미리 포함되어야 한다.
 
// 컴파일러는 cpp 파일에서 선언보다 헤더 파일 선언을 먼저 확인하기 때문에,
// cpp 파일은 컴파일러가 나중에 해석한다.(컴파일 이후 링크 단계에서)
// 따라서 헤더에 필요한 정보를 포함하지 않으면 cpp에서 헤더를 include 하더라도 이미 컴파일 오류가 발생한다.

class CScene_Start :
	public CScene
{
public:
	CScene_Start();
	~CScene_Start();
};