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
						 }\
					 private:\
						type();\
						~type();

// 델타 타임(프레임 사이의 흐른 시간) 반환 매크로 함수
#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

enum class GROUP_TYPE
{
	DEFAULT,

	PLAYER,

	MISSILE,

	MONSTER,

	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};