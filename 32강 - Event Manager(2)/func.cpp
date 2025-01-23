#include "pch.h"
#include "func.h"
#include "CEventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	// ������ �ּҴ� 16 ���� ������ ���� ������ �������� ��ü ũ�� ������ �Ϲ� ������ ������ �� �ִ�.
	// �������� ũ��� 32 ��Ʈ ȯ�濡�� 4 ����Ʈ, 64 ��Ʈ ȯ�濡�� 8 ����Ʈ��.
	// ���� ��� ���� lParam �� Ÿ���� 4 ����Ʈ or 8 ����Ʈ�� �������� DWORD_PTR �ڷ����̹Ƿ�,
	// DWORD_PTR Ÿ������ ����ȯ�Ͽ� �����Ѵ�.
	evn.wParam = (DWORD_PTR)_eGroup; // enum ���� 4 ����Ʈ �������̴�.

	CEventMgr::GetInst()->AddEvent(evn);
}
