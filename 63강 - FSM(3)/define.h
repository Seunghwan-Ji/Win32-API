#pragma once

// �̱��� ��ũ�� �Լ�.
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

// ��Ÿ Ÿ��(������ ������ �帥 �ð�) ��ȯ ��ũ�� �Լ�.
#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

// ������Ʈ ���� ��ũ�� �Լ�.
#define CLONE(type) type* Clone() { return new type(*this); }

// Ű �Է� Ȯ�� ��ũ�� �Լ�.
#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

// ���콺 Ŀ�� ��ǥ Ȯ�� ��ũ�� �Լ�.
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define PI 3.1415926535f // ����(��) ����.

#define TILE_SIZE 64 // �� Ÿ�� �� ĭ�� �ȼ� ��(��ġ�� 2�� �¼��� �����ϴ°� �Ϲ���)

// ������Ʈ ����.
enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	MONSTER,
	PLAYER,
	PROJ_PLAYER,  // �÷��̾��� ����ü.
	PROJ_MONSTER, // ������ ����ü.

	UI = 31, // UI �� ���� �������� �׸���.
	END = 32,
};

// �� ����.
enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

// ������Ʈ �浹 ���� ǥ�ÿ� DC�� ����� �� �� �귯�� ����.
enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

// �̺�Ʈ ����.
enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,
	END,
};

// ���� ���� ����.
enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATT,
	RUN,
	DEAD,
};