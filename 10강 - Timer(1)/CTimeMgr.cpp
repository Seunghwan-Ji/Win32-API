#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llFrequency{}
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	QueryPerformanceCounter(&m_llCurCount);
	// GetTickCount �Լ����� �� �����ϰ� ī��Ʈ�� �����ϴ� �Լ�.

	QueryPerformanceFrequency(&m_llFrequency);
	// �ʴ� ī��Ʈ�� �󸶳� �߻��ϴ��� �˾ƺ��� �Լ�.
	// ������� ���� Ȯ���غ��� �ʴ� õ�� ī��Ʈ�� ���´�.
}
