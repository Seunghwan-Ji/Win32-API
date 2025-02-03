#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
{

}

CCamera::~CCamera()
{

}

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	// ī�޶� ����.
	if (KEY_HOLD(KEY::W))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::S))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::A))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::D))
		m_vLookAt.x += 500.f * fDT;

	// ȭ�� �߾� ��ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���.
	CalDiff();
}

void CCamera::CalDiff()
{
	// ī�޶� �̵� ȿ�� ����.
	// ���� LookAt �� ���� Look �� ���̰��� �����ؼ� ������ LookAt �� ���Ѵ�.
	Vec2 vLookDir = m_vLookAt - m_PrevLookAt;

	m_vCurLookAt = m_PrevLookAt + vLookDir.Normalize() * 500.f * fDT;

	Vec2 vResolution = CCore::GetInst()->GetResolution(); // �ػ�.
	Vec2 vCenter = vResolution / 2; // �ػ� �߽� ��ǥ.

	m_vDiff = m_vCurLookAt - vCenter;
	m_PrevLookAt = m_vCurLookAt;
}
