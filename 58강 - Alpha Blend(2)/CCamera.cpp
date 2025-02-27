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

	// 카메라 조작.
	if (KEY_HOLD(KEY::W))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::S))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::A))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::D))
		m_vLookAt.x += 500.f * fDT;

	// 화면 중앙 좌표와 카메라 LookAt 좌표간의 차이값 계산.
	CalDiff();
}

void CCamera::render(HDC _dc)
{
	if (CAM_EFFECT::NONE == m_eEffect)
		return;

	float fRatio = 0.f; // 이펙트 진행 비율.

	if (CAM_EFFECT::FADE_OUT == m_eEffect)
	{
		// 시간 누적값을 체크.
		m_fCurTime += fDT;

		// 진행 시간이 이펙트 최대 지정 시간을 넘어선 경우.
		if (m_fEffectDuration < m_fCurTime)
		{
			// 효과 종료.
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
		// 렌더링 목적지 시작 좌표 및 스케일.
		, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		// 텍스처 DC.
		, m_pVeilTex->GetDC()
		// 텍스처에서 복사를 시작할 좌표 및 스케일.
		, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		// 위 양식대로 작성된 객체를 넣는 이 함수의 마지막 옵션.
		, bf);
}

void CCamera::CalDiff()
{
	// 카메라 이동 효과 구현.
	// 이전 LookAt 과 현재 Look 의 차이값을 보정해서 현재의 LookAt 을 구한다.
	m_fAccTime += fDT;

	// m_fAccTime이 m_fTime보다 커지면 카메라는 목표 위치(m_vLookAt)에 도달했다고 간주함.
	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		// 목표 좌표와 이전 프레임의 카메라 위치 간의 방향 벡터.
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

		// 씬 전환 시 이전 씬과 카메라 위치가 같을 때, vLookDir 이 0 이 되면서
		// 정규화가 불가능해 지는 것을 방지하는 예외 처리.
		if (!vLookDir.IsZero())
		{
			// 현재 카메라 위치를 이전 위치에서 목표 방향으로 보간한 새로운 위치로 업데이트
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
			// vLookDir.Normalize(): 방향 벡터를 단위 벡터로 변환.
			// m_fSpeed * fDT: 이번 프레임에서 카메라가 이동해야 할 거리.
			// 방향(단위 벡터) * 이동 거리 = 이동 벡터.
			// 이전 위치 + 이동 벡터 → 새로운 위치.
		}
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution(); // 해상도.
	Vec2 vCenter = vResolution / 2; // 해상도 중심 좌표.

	// 화면 해상도의 중심과 카메라 위치의 차이를 구해 m_vDiff에 저장.
	m_vDiff = m_vCurLookAt - vCenter;

	// m_vPrevLookAt에 현재 프레임의 카메라 보정 위치를 저장하여 다음 프레임에서 보간 처리를 이어감.
	m_vPrevLookAt = m_vCurLookAt;
}
