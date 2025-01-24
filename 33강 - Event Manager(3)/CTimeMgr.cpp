#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);

	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	// ���� ī��Ʈ ���� ���� ������ ����(�������� ����� ���ؼ�)
	m_llPrevCount = m_llCurCount;

#ifdef _DEBUG // ����� ��忡���� ����Ǵ� ��ó���� ����.
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.); // ������߿� �ð��� ���� �귯�� DT ���� Ŀ�� �� Ư�� ��ġ�� ����.
#endif
}

void CTimeMgr::render()
{
	++m_iCallCount;
	m_dAcc += m_dDT; // DT ����.

	if (m_dAcc >= 1.) // 1�ʰ� �귶�ٸ�.
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		// �迭�� ���ڿ� ����
		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS: %d, DT: %f", m_iFPS, m_dDT);

		// ����� ���ڿ� �迭�� ������ Ÿ��Ʋ�ٿ� ���
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
