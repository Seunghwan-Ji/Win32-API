#pragma once

class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];

public:
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight); // 그룹 간 충돌 검사.
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }
	// memset: 지정한 주소를, 지정한 값으로 바이트 단위로 세팅하는 함수.
};
