#pragma once

class CObject; // 전방 선언, 헤더와 헤더끼리 서로를 참조하는 것을 최대한 방지.

class CScene
{
private:
	// 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언.
	// UINT: Unsigned Integer
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 벡터 배열의 크기를 END 만큼 설정.
	wstring			 m_strName; // Scene 이름.

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update();
	void render(HDC _dc);

	// 부모 포인터로 자식 쪽의 Enter, Exit 함수를 호출하기 위해,
	// 부모쪽에서 가상 함수로 정의 해준다.
	virtual void Enter() = 0; // 해당 Scene 에 진입 시 호출.
	virtual void Exit() = 0;  // 해당 Scene 에 탈출 시 호출.

protected: // 자식쪽에서 접근할 수 있도록 protected 로 선언.
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }
	// 함수 호출 비용을 없애기 위해 함수를 헤더에 구현, 인라인 처리.
	// 호출한 쪽 스택에서 처리함.

public:
	CScene();
	virtual ~CScene(); // 이 클래스를 상속받은 자식 클래스에서 소멸자를 호출할 때,
	// 자식쪽의 소멸자를 호출해야 하므로 가상 함수로 정의한다.
};

