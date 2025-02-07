#pragma once

#include "global.h"
#include "CCamera.h" // 카메라는 모든 오브젝트가 사용하기 때문에, 헤더 파일에 작성하기로 함.

class CCollider;
class CAnimator;

class CObject
{
private:
	wstring    m_strName; // 오브젝트를 구별하는 이름.

	Vec2	   m_vPos;
	Vec2	   m_vScale;

	// Component
	CCollider* m_pCollider; // 충돌 기능이 필요한 오브젝트를 위한 멤버 변수.
	CAnimator* m_pAnimator; // 애니메이션들을 관리하는 객체의 주소.

	bool	   m_bAlive; // 오브젝트 활성화 여부.

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }

	bool IsDead() { return !m_bAlive; }

	void CreateCollider();
	void CreateAnimator();

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	void SetDead() { m_bAlive = false; } // CEventMgr 가 호출하는 함수.

public:
	virtual void update() = 0; // 파생된 객체들의 자체 업데이트 함수 호출을 위한 순수 가상 함수.
	virtual void finalupdate(); // CAnimator 에서 오버라이딩 하기 위해 임시로 final 키워드 삭제.
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

	virtual CObject* Clone() = 0; // 자기 자신의 복제 버전을 되돌려주는 함수.(자식쪽에서 오버라이딩)

public:
	CObject();
	CObject(const CObject& _origin); // 오브젝트 복사 생성자.
	virtual ~CObject();

	friend class CEventMgr;
};
