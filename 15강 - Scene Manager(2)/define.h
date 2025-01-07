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

// ��Ÿ Ÿ��(������ ������ �帥 �ð�) ��ȯ ��ũ�� �Լ�
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