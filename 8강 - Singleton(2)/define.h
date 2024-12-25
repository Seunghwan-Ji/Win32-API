#pragma once

// 싱글톤 매크로 함수
// #define SINGLE(type) public: static type* GetInst() {static type mgr; return &mgr;}
// mgr: manager 약자

// \ 를 사용하면 다음 줄도 전처리기 치환 구문에 포함되어 매크로 정의를 이어갈 수 있다.
#define SINGLE(type) public:\
						 static type* GetInst()\
						 {\
							 static type mgr;\
							 \
							 return &mgr;\
						 }
