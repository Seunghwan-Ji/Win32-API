#pragma once

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];

public:
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight); // �׷� �� �浹 �˻�.
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }
	// memset: ������ �ּҸ�, ������ ������ ����Ʈ ������ �����ϴ� �Լ�.
};
