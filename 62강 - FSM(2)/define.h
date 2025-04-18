#pragma once

// 싱글톤 매크로 함수.
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

// 델타 타임(프레임 사이의 흐른 시간) 반환 매크로 함수.
#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

// 오브젝트 복제 매크로 함수.
#define CLONE(type) type* Clone() { return new type(*this); }

// 키 입력 확인 매크로 함수.
#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

// 마우스 커서 좌표 확인 매크로 함수.
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define PI 3.1415926535f // 파이(π) 정의.

#define TILE_SIZE 64 // 맵 타일 한 칸의 픽셀 수(수치는 2의 승수로 조정하는게 일반적)

// 오브젝트 종류.
enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	MONSTER,
	PLAYER,
	PROJ_PLAYER,  // 플레이어의 투사체.
	PROJ_MONSTER, // 몬스터의 투사체.

	UI = 31, // UI 는 가장 마지막에 그린다.
	END = 32,
};

// 씬 종류.
enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

// 오브젝트 충돌 영역 표시에 DC가 사용할 펜 및 브러쉬 종류.
enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

// 이벤트 종류.
enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	END,
};

// 몬스터 상태 종류.
enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATT,
	RUN,
	DEAD,
};