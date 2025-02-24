#pragma once

#include "global.h"

class CObject; // 전방 선언, 헤더와 헤더끼리 서로를 참조하는 것을 최대한 방지.

class CScene
{
private:
	// 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언.
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 벡터 배열의 크기를 END 만큼 설정.
	wstring			 m_strName; // Scene 이름.

	UINT			 m_iTileX; // 타일 가로 개수.
	UINT			 m_iTileY; // 타일 세로 개수.

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	virtual void Enter() = 0; // 해당 Scene 에 진입 시 호출.
	virtual void Exit() = 0;  // 해당 Scene 에 탈출 시 호출.

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	// 원본을 반환을 위해 레퍼런스를 붙이고, 원본 훼손을 막기 위해 상수화해서 반환.

	void DeleteGroup(GROUP_TYPE _eTarget); // 지정한 오브젝트 그룹을 비우는 함수.
	void DeleteAll(); // 모든 오브젝트 그룹을 비우는 함수.
	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);

	// UI 그룹을 수정할 수 있도록 참조 형태로 반환하는 함수.
	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

public:
	CScene();
	virtual ~CScene();
};