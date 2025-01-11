#pragma once

class CObject; // 전방 선언, 헤더와 헤더끼리 서로를 참조하는 것을 최대한 방지.

class CScene
{
private:
	// 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언.
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 벡터 배열의 크기를 END 만큼 설정.
	wstring			 m_strName; // Scene 이름.

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update();
	void render(HDC _dc);

	virtual void Enter() = 0; // 해당 Scene 에 진입 시 호출.
	virtual void Exit() = 0;  // 해당 Scene 에 탈출 시 호출.

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }

public:
	CScene();
	virtual ~CScene();
};