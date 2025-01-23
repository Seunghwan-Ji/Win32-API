#pragma once

struct tEvent
{
	EVENT_TYPE eEven;
	DWORD	   lParam;
	DWORD	   wParam;
};
// DWORD: unsigned long, 32비트와 64비트 환경에서 부호 없는 4 바이트 정수 자료형.

class CEventMgr
{
	SINGLE(CEventMgr)
private:
	vector<tEvent> m_vecEvent;

public:
	void update();
};

