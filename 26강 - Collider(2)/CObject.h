#pragma once

class CCollider;

class CObject
{
private:
	Vec2	   m_vPos;
	Vec2	   m_vScale;

	CCollider* m_pCollider; // 충돌 기능이 필요한 오브젝트를 위한 멤버 변수.

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	CCollider* GetCollider() { return m_pCollider; }

	void CreateCollider();

public:
	virtual void update() = 0; // 파생된 객체들의 자체 업데이트 함수 호출을 위한 순수 가상 함수.
	virtual void finalupdate() final; // 이 클래스 전용 함수, 자식쪽에서 오버라이딩 금지.
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

public:
	CObject();
	virtual ~CObject();
};
