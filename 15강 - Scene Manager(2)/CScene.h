#pragma once

class CObject; // 전방 선언, 헤더와 헤더끼리 서로를 참조하는 것을 최대한 방지.

class CScene
{
private:
	// 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언.
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // UINT: Unsigned Integer
	wstring			 m_strName; // Scene 이름.

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

public:
	CScene();
	virtual ~CScene(); // 이 클래스를 상속받은 자식 클래스에서 소멸자를 호출할 때,
	// 자식쪽의 소멸자를 호출해야 하므로 가상 함수로 정의한다.
};

