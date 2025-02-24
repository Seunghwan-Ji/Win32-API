#pragma once

#include "global.h"

class CObject; // ���� ����, ����� ������� ���θ� �����ϴ� ���� �ִ��� ����.

class CScene
{
private:
	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����.
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // ���� �迭�� ũ�⸦ END ��ŭ ����.
	wstring			 m_strName; // Scene �̸�.

	UINT			 m_iTileX; // Ÿ�� ���� ����.
	UINT			 m_iTileY; // Ÿ�� ���� ����.

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	virtual void Enter() = 0; // �ش� Scene �� ���� �� ȣ��.
	virtual void Exit() = 0;  // �ش� Scene �� Ż�� �� ȣ��.

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	// ������ ��ȯ�� ���� ���۷����� ���̰�, ���� �Ѽ��� ���� ���� ���ȭ�ؼ� ��ȯ.

	void DeleteGroup(GROUP_TYPE _eTarget); // ������ ������Ʈ �׷��� ���� �Լ�.
	void DeleteAll(); // ��� ������Ʈ �׷��� ���� �Լ�.
	void CreateTile(UINT _iXCount, UINT _iYCount);
	void LoadTile(const wstring& _strRelativePath);

	// UI �׷��� ������ �� �ֵ��� ���� ���·� ��ȯ�ϴ� �Լ�.
	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

public:
	CScene();
	virtual ~CScene();
};