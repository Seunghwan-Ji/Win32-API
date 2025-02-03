#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.f)
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
	m_fAccTime += fDT;

	// m_fAccTime�� m_fTime���� Ŀ���� ī�޶�� ��ǥ ��ġ(m_vLookAt)�� �����ߴٰ� ������.
	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		// ��ǥ ��ǥ�� ���� �������� ī�޶� ��ġ ���� ���� ����.
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

		// ���� ī�޶� ��ġ�� ���� ��ġ���� ��ǥ �������� ������ ���ο� ��ġ�� ������Ʈ
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
		// vLookDir.Normalize(): ���� ���͸� ���� ���ͷ� ��ȯ.
		// m_fSpeed * fDT: �̹� �����ӿ��� ī�޶� �̵��ؾ� �� �Ÿ�.
		// ����(���� ����) * �̵� �Ÿ� = �̵� ����.
		// ���� ��ġ + �̵� ���� �� ���ο� ��ġ.
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution(); // �ػ�.
	Vec2 vCenter = vResolution / 2; // �ػ� �߽� ��ǥ.

	// ȭ�� �ػ��� �߽ɰ� ī�޶� ��ġ�� ���̸� ���� m_vDiff�� ����.
	m_vDiff = m_vCurLookAt - vCenter;

	// m_vPrevLookAt�� ���� �������� ī�޶� ���� ��ġ�� �����Ͽ� ���� �����ӿ��� ���� ó���� �̾.
	m_vPrevLookAt = m_vCurLookAt;
}
