#pragma once

class CObject; // ���� ����, ����� ������� ���θ� �����ϴ� ���� �ִ��� ����.

class CScene
{
private:
	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����.
	// UINT: Unsigned Integer
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // ���� �迭�� ũ�⸦ END ��ŭ ����.
	wstring			 m_strName; // Scene �̸�.

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update();
	void render(HDC _dc);

	// �θ� �����ͷ� �ڽ� ���� Enter, Exit �Լ��� ȣ���ϱ� ����,
	// �θ��ʿ��� ���� �Լ��� ���� ���ش�.
	virtual void Enter() = 0; // �ش� Scene �� ���� �� ȣ��.
	virtual void Exit() = 0;  // �ش� Scene �� Ż�� �� ȣ��.

protected: // �ڽ��ʿ��� ������ �� �ֵ��� protected �� ����.
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); }
	// �Լ� ȣ�� ����� ���ֱ� ���� �Լ��� ����� ����, �ζ��� ó��.
	// ȣ���� �� ���ÿ��� ó����.

public:
	CScene();
	virtual ~CScene(); // �� Ŭ������ ��ӹ��� �ڽ� Ŭ�������� �Ҹ��ڸ� ȣ���� ��,
	// �ڽ����� �Ҹ��ڸ� ȣ���ؾ� �ϹǷ� ���� �Լ��� �����Ѵ�.
};

