#pragma once

struct tEvent
{
	EVENT_TYPE eEven;
	DWORD	   lParam;
	DWORD	   wParam;
};
// DWORD: unsigned long, 32��Ʈ�� 64��Ʈ ȯ�濡�� ��ȣ ���� 4 ����Ʈ ���� �ڷ���.

class CEventMgr
{
	SINGLE(CEventMgr)
private:
	vector<tEvent> m_vecEvent;

public:
	void update();
};

