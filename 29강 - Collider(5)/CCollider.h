#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID; // 객체에 포함되지 않는 정적 멤버 변수.

	CObject* m_pOwner;	   // collider 를 소유하고 있는 오브젝트.
	Vec2	 m_vOffsetPos; // 오브젝트로부터 상대적인 위치.
	Vec2	 m_vFinalPos;  // finalupdate 에서 매 프레임마다 계산.
	Vec2	 m_vScale;     // 충돌 영역의 사이즈.

	UINT	 m_iID;		   // 충돌 영역의 고유한 ID 값.

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	UINT GetID() { return m_iID; }

public:
	void finalupdate(); // 충돌 영역을 오브젝트의 위치로 이동.
	void render(HDC _dc);

public:
	// 충돌 시점 함수.
	void OnCollision(CCollider* _pOther); // 충돌중인 경우 호출되는 함수.
	void OnCollisionEnter(CCollider* _pOther); // 충돌 진입 시 호출되는 함수.
	void OnCollisionExit(CCollider* _pOther); // 충돌 해제 시 호출되는 함수.

	CCollider& operator = (CCollider& _origin) = delete;
	// CCollider 객체끼리는 값을 복사받지 못하게 함.
	// 대입 연산자 함수 삭제.

public:
	CCollider();
	CCollider(const CCollider& _origin); // 복사 생성자.(충돌 영역 복사)
	~CCollider();

	friend class CObject;
};
