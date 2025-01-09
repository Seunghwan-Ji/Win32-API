#pragma once

class CObject
{
private:
	Vec2 m_vPos;
	Vec2 m_vScale;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	virtual void update() = 0; // 파생된 객체들의 자체 업데이트 함수 호출을 위한 순수 가상 함수.
	// 순수 가상 함수: 구현이 없이 선언만 되어 있는 함수.
	// 순수 가상 함수는 함수 선언 끝에 = 0을 붙여서 정의함.
	// 이 함수는 기본 클래스에서는 구현되지 않으며, 상속받은 자식 클래스에서 구현해야함.
	// 순수 가상 함수를 포함하는 클래스는 추상 클래스가 되며, 이 클래스 자체는 객체를 생성할 수 없음.
	// 자식 클래스에서는 반드시 이 순수 가상 함수를 오버라이드(재정의)하여 구현해야만,
	// 자식 클래스의 객체를 생성할 수 있음.

	// 여기서 사용하는 이유
	// update() 함수는 게임 내 모든 오브젝트가 갖춰야 할 공통적인 메서드.
	// 순수 가상 함수는 자식 클래스에서 재정의된 메서드를 통해 다형성을 활용할 수 있게 함.
	// 즉, 부모 클래스 타입으로 자식 클래스의 update() 함수를 호출할 수 있게 됨.
	virtual void render(HDC _dc);

public:
	CObject();
	virtual ~CObject();
};
