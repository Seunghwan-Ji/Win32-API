#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
	, m_eEffect(CAM_EFFECT::NONE)
	, m_pVeilTex(nullptr)
	, m_fEffectDuration(0.f)
	, m_fCurTime(0.f)
{
}

CCamera::~CCamera()
{

}

void CCamera::init()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
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

void CCamera::render(HDC _dc)
{
	if (CAM_EFFECT::NONE == m_eEffect)
		return;

	float fRatio = 0.f; // ����Ʈ ���� ����.

	if (CAM_EFFECT::FADE_OUT == m_eEffect)
	{
		// �ð� �������� üũ.
		m_fCurTime += fDT;

		// ���� �ð��� ����Ʈ �ִ� ���� �ð��� �Ѿ ���.
		if (m_fEffectDuration < m_fCurTime)
		{
			// ȿ�� ����.
			m_eEffect = CAM_EFFECT::NONE;
			return;
		}

		fRatio = m_fCurTime / m_fEffectDuration;
	}

	int iAlpha = (int)(255.f * fRatio);

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	AlphaBlend(_dc
		// ������ ������ ���� ��ǥ �� ������.
		, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		// �ؽ�ó DC.
		, m_pVeilTex->GetDC()
		// �ؽ�ó���� ���縦 ������ ��ǥ �� ������.
		, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		// �� ��Ĵ�� �ۼ��� ��ü�� �ִ� �� �Լ��� ������ �ɼ�.
		, bf);
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

		// �� ��ȯ �� ���� ���� ī�޶� ��ġ�� ���� ��, vLookDir �� 0 �� �Ǹ鼭
		// ����ȭ�� �Ұ����� ���� ���� �����ϴ� ���� ó��.
		if (!vLookDir.IsZero())
		{
			// ���� ī�޶� ��ġ�� ���� ��ġ���� ��ǥ �������� ������ ���ο� ��ġ�� ������Ʈ
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
			// vLookDir.Normalize(): ���� ���͸� ���� ���ͷ� ��ȯ.
			// m_fSpeed * fDT: �̹� �����ӿ��� ī�޶� �̵��ؾ� �� �Ÿ�.
			// ����(���� ����) * �̵� �Ÿ� = �̵� ����.
			// ���� ��ġ + �̵� ���� �� ���ο� ��ġ.
		}
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution(); // �ػ�.
	Vec2 vCenter = vResolution / 2; // �ػ� �߽� ��ǥ.

	// ȭ�� �ػ��� �߽ɰ� ī�޶� ��ġ�� ���̸� ���� m_vDiff�� ����.
	m_vDiff = m_vCurLookAt - vCenter;

	// m_vPrevLookAt�� ���� �������� ī�޶� ���� ��ġ�� �����Ͽ� ���� �����ӿ��� ���� ó���� �̾.
	m_vPrevLookAt = m_vCurLookAt;
}
