#pragma once

class CCollider;

union Test
{
	int a;
	float f;
};
// union: 제일 큰 멤버의 사이즈 기준으로 같은 공간을 공유한다.
// 위 유니온은 4바이트 공간의 비트를 정수 또는 실수로 해석할 수 있다.

union COLLIDER_ID // 8 바이트 유니온.
{
	struct {
		UINT Left_id;  // 충돌체 1 의 ID.
		UINT Right_id; // 충돌체 2 의 ID.
	};

	ULONGLONG ID; // 8 바이트 멤버.
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	map<ULONGLONG, bool> m_mapColInfo; // 충돌체 간의 이전 프레임 충돌 정보.
	UINT			    m_arrCheck[(UINT)GROUP_TYPE::END]; // 그룹간의 충돌 체크 매트릭스.

public:
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight); // 그룹 간 충돌 검사.
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol); // 충돌 검사 함수.
};
