#include "pch.h"
#include "func.h"
#include "CEventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	// 포인터 주소는 16 진수 형태의 정수 값으로 포인터의 자체 크기 단위로 일반 변수에 저장할 수 있다.
	// 포인터의 크기는 32 비트 환경에서 4 바이트, 64 비트 환경에서 8 바이트다.
	// 따라서 멤버 변수 lParam 의 타입이 4 바이트 or 8 바이트인 유동적인 DWORD_PTR 자료형이므로,
	// DWORD_PTR 타입으로 형변환하여 저장한다.
	evn.wParam = (DWORD_PTR)_eGroup; // enum 값은 4 바이트 정수형이다.

	CEventMgr::GetInst()->AddEvent(evn);
}
