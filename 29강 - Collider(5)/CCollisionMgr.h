#pragma once

class CCollider;

union Test
{
	int a;
	float f;
};
// union: ���� ū ����� ������ �������� ���� ������ �����Ѵ�.
// �� ���Ͽ��� 4����Ʈ ������ ��Ʈ�� ���� �Ǵ� �Ǽ��� �ؼ��� �� �ִ�.

union COLLIDER_ID // 8 ����Ʈ ���Ͽ�.
{
	struct {
		UINT Left_id;  // �浹ü 1 �� ID.
		UINT Right_id; // �浹ü 2 �� ID.
	};

	ULONGLONG ID; // 8 ����Ʈ ���.
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	map<ULONGLONG, bool> m_mapColInfo; // �浹ü ���� ���� ������ �浹 ����.
	UINT			    m_arrCheck[(UINT)GROUP_TYPE::END]; // �׷찣�� �浹 üũ ��Ʈ����.

public:
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight); // �׷� �� �浹 �˻�.
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol); // �浹 �˻� �Լ�.
};
