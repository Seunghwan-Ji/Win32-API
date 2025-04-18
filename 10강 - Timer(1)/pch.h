#pragma once

// 미리 컴파일된 헤더
#include <Windows.h> // 윈도우 기능 헤더.
#include <iostream>

#include "define.h"
#include "struct.h"

// 프로젝트 우클릭 -> 속성 -> C/C++ -> 미리 컴파일된 헤더 -> 만들기 ->
// 미리 컴파일된 헤더 파일 이름: pch.h -> 적용, 확인

// 미리 컴파일된 헤더 파일이 만들어지면, 해당 프로젝트 내 모든 cpp 파일들은
// #include "pch.h" 이 구문이 추가되지 않으면 컴파일 에러가 발생한다.
// 추가할 다른 전처리기도 있다면, 위 구문부터 작성해야 한다.

// 컴파일의 속도를 올리기 위해 만들어진 시스템이다.
// 다시 확인해 볼 필요 없는, 완성되어 있는 코드들을 include 구문으로 여기에 추가하면,
// 해당 코드들을 재 컴파일 하지 않는다.
// 클래스를 생성할 때, cpp 파일에서 자동으로 #include "pch.h" 구문이 추가된다.