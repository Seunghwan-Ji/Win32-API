#pragma once

struct tEvent
{
	EVENT_TYPE eEven;
	DWORD_PTR  lParam;
	DWORD_PTR  wParam;
};
// DWORD_PTR: 32 ��Ʈ ȯ�濡���� 4 ����Ʈ unsigned long,
// 64 ��Ʈ ȯ�濡���� 8 ����Ʈ unsigned long long Ÿ������ ���������� ���ǵ� �ڷ���.

class CEventMgr
{
	SINGLE(CEventMgr)
private:
	vector<tEvent> m_vecEvent; // �߻��� �̺�Ʈ ���.

	vector<CObject*> m_vecDead; // ���� ������ ������Ʈ ���.

public:
	void update();

private:
	void Excute(const tEvent& _eve); // �̺�Ʈ ó�� �Լ�.

public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); } // �߻��� �̺�Ʈ �߰� �Լ�.
};

