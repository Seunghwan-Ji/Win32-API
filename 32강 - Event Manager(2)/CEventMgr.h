#pragma once

struct tEvent
{
	EVENT_TYPE eEven;
	DWORD_PTR  lParam;
	DWORD_PTR  wParam;
};
// DWORD_PTR: 32 비트 환경에서는 4 바이트 unsigned long,
// 64 비트 환경에서는 8 바이트 unsigned long long 타입으로 유동적으로 정의된 자료형.

class CEventMgr
{
	SINGLE(CEventMgr)
private:
	vector<tEvent> m_vecEvent; // 발생한 이벤트 목록.

	vector<CObject*> m_vecDead; // 삭제 예정된 오브젝트 목록.

public:
	void update();

private:
	void Excute(const tEvent& _eve); // 이벤트 처리 함수.

public:
	void AddEvent(const tEvent& _eve) { m_vecEvent.push_back(_eve); } // 발생한 이벤트 추가 함수.
};

