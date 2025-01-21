#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID; // ��ü�� ���Ե��� �ʴ� ���� ��� ����.

	CObject* m_pOwner;	   // collider �� �����ϰ� �ִ� ������Ʈ.
	Vec2	 m_vOffsetPos; // ������Ʈ�κ��� ������� ��ġ.
	Vec2	 m_vFinalPos;  // finalupdate ���� �� �����Ӹ��� ���.
	Vec2	 m_vScale;     // �浹 ������ ������.

	UINT	 m_iID;		   // �浹 ������ ������ ID ��.

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	UINT GetID() { return m_iID; }

public:
	void finalupdate(); // �浹 ������ ������Ʈ�� ��ġ�� �̵�.
	void render(HDC _dc);

public:
	// �浹 ���� �Լ�.
	void OnCollision(CCollider* _pOther); // �浹���� ��� ȣ��Ǵ� �Լ�.
	void OnCollisionEnter(CCollider* _pOther); // �浹 ���� �� ȣ��Ǵ� �Լ�.
	void OnCollisionExit(CCollider* _pOther); // �浹 ���� �� ȣ��Ǵ� �Լ�.

	CCollider& operator = (CCollider& _origin) = delete;
	// CCollider ��ü������ ���� ������� ���ϰ� ��.
	// ���� ������ �Լ� ����.

public:
	CCollider();
	CCollider(const CCollider& _origin); // ���� ������.(�浹 ���� ����)
	~CCollider();

	friend class CObject;
};
