#pragma once

#include "global.h"
#include "CCamera.h" // ī�޶�� ��� ������Ʈ�� ����ϱ� ������, ��� ���Ͽ� �ۼ��ϱ�� ��.

class CCollider;
class CAnimator;
class CRigidBody;
class CGravity;

class CObject
{
private:
	wstring    m_strName; // ������Ʈ�� �����ϴ� �̸�.

	Vec2	   m_vPos;
	Vec2	   m_vScale;

	// Component
	CCollider*  m_pCollider; // �浹 ����� �ʿ��� ������Ʈ�� ���� ��� ����.
	CAnimator*  m_pAnimator; // �ִϸ��̼ǵ��� �����ϴ� ��ü�� �ּ�.
	CRigidBody* m_pRigidBody; // �������� ȿ���� �ֱ� ���� ��ü ��� ��� ����.
	CGravity*   m_pGravity;

	bool	   m_bAlive; // ������Ʈ Ȱ��ȭ ����.

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	CGravity* GetGravity() { return m_pGravity; }

	bool IsDead() { return !m_bAlive; }

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGravitiy();

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	void SetDead() { m_bAlive = false; } // CEventMgr �� ȣ���ϴ� �Լ�.

public:
	virtual void start() {}; // Scene �� ���۵Ǳ� ������ ȣ��Ǵ� �Լ�.
	virtual void update() = 0; // �Ļ��� ��ü���� ��ü ������Ʈ �Լ� ȣ���� ���� ���� ���� �Լ�.
	virtual void finalupdate(); // CAnimator ���� �������̵� �ϱ� ���� �ӽ÷� final Ű���� ����.
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

	virtual CObject* Clone() = 0; // �ڱ� �ڽ��� ���� ������ �ǵ����ִ� �Լ�.(�ڽ��ʿ��� �������̵�)

public:
	CObject();
	CObject(const CObject& _origin); // ������Ʈ ���� ������.
	virtual ~CObject();

	friend class CEventMgr;
};
