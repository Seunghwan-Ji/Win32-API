#pragma once

class CObject;

class CCollider
{
private:
	CObject* m_pOwner; // 이 충돌 영역의 주인이 되는 오브젝트.

public:
	void finalupdate(); // 충돌 영역을 오브젝트의 위치로 이동.

	friend class CObject;
};
