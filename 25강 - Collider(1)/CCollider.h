#pragma once

class CObject;

class CCollider
{
private:
	CObject* m_pOwner; // �� �浹 ������ ������ �Ǵ� ������Ʈ.

public:
	void finalupdate(); // �浹 ������ ������Ʈ�� ��ġ�� �̵�.

	friend class CObject;
};
