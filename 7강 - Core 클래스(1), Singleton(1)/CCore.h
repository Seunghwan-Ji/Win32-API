#pragma once

// �̱��� ����
// ��ü�� ������ 1���� ����.
// ��𼭵� ���� ���� ����.
class CCore
{
private:
	static CCore* g_pInst; // ������ ������ ���� ��� ���� �Ҵ�.

public:
	// ���� ��� �Լ�
	static CCore* GetInstance()
	{
		// ���� ȣ��� ���
		if (nullptr == g_pInst)
		{
			g_pInst = new CCore;
		}

		return g_pInst;
	}

	// ���� ��� ���� �޸� ���� �Լ�
	static void Release()
	{
		if (nullptr != g_pInst)
		{
			delete g_pInst; // �޸� ����.
			g_pInst = nullptr; // ���� ��� �Լ� ȣ���, �޸� �Ҵ��� ���� �ּҰ� ����.
		}
	}

private:
	// �����ڸ� private ���� �����Ͽ�, �ܺο��� ��ü�� �������� ���ϰ� ����.
	CCore() {}
	~CCore() {}
};

// ���� ��� ������ �ּҰ��� ������ ������, �ּҷ� �������� ���� �� ���� �� ������ �����Ѵ�.