#pragma once

// �̱��� ��ũ�� �Լ�
// #define SINGLE(type) public: static type* GetInst() {static type mgr; return &mgr;}
// mgr: manager ����

// \ �� ����ϸ� ���� �ٵ� ��ó���� ġȯ ������ ���ԵǾ� ��ũ�� ���Ǹ� �̾ �� �ִ�.
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

// Ű �Է� Ȯ�� ��ũ��.
#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

#define PI 3.1415926535f // ����

// ������Ʈ ���� ��ũ��.
enum class GROUP_TYPE
{
	DEFAULT,

	PLAYER,

	MISSILE,

	MONSTER,

	END = 32,
};

// �� ���� ��ũ��.
enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};