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
	, m_pVeilTex(nullptr)
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
	if (m_listCamEffect.empty())
		return;

	// �ð� �������� üũ.
	tCamEffect& effect = m_listCamEffect.front();
	effect.fCurTime += fDT;

	

	float fRatio = 0.f; // ����Ʈ ���� ����.
	fRatio = effect.fCurTime / effect.fDuration;

	if (fRatio < 0.f)
		fRatio = 0.f;
	if (fRatio > 1.f)
		fRatio = 1.f;

	int iAlpha = 0;

	if (CAM_EFFECT::FADE_OUT == effect.eEffect)
	{
		// ���� ���� ������ ���� ��ο� ������ ��ȭ.
		iAlpha = (int)(255.f * fRatio);
	}
	else if (CAM_EFFECT::FADE_IN == effect.eEffect)
	{
		// ���� ������� ���� ���� fRatio�� �ݴ��̹Ƿ�, 1 ���� ���ش�.
		iAlpha = (int)(255.f * (1.f - fRatio));
	}

	BLENDFUNCTION bf = {};
	// ���� ��� ���� ���ο� �̹����� ���� ����� ���(Alpha Blending) �� ���.
	bf.BlendOp = AC_SRC_OVER;
	
	// ������ �ʴ� �ʵ��̹Ƿ� �׻� 0���� ����.
	bf.BlendFlags = 0;
	
	// �̹��� ��ü�� ���� ä��(���� ����)�� ���ٰ� ����.
	// ��, SourceConstantAlpha ���� ���� ������ ���.
	bf.AlphaFormat = 0;
	
	// ��ü �̹����� ����(0~255)�� ����.
	// ���� Ŭ���� ������, �������� ����.
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

	// ���� �ð��� ����Ʈ �ִ� ���� �ð��� �Ѿ ���.
	if (effect.fDuration < effect.fCurTime)
	{
		// ȿ�� ����.
		m_listCamEffect.pop_front(); // ����Ʈ���� ù ��° ȿ�� ����ü ����.
	}
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
