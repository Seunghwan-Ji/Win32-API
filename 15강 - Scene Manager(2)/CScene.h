#pragma once

class CObject; // ���� ����, ����� ������� ���θ� �����ϴ� ���� �ִ��� ����.

class CScene
{
private:
	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����.
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // UINT: Unsigned Integer
	wstring			 m_strName; // Scene �̸�.

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

public:
	CScene();
	virtual ~CScene(); // �� Ŭ������ ��ӹ��� �ڽ� Ŭ�������� �Ҹ��ڸ� ȣ���� ��,
	// �ڽ����� �Ҹ��ڸ� ȣ���ؾ� �ϹǷ� ���� �Լ��� �����Ѵ�.
};

