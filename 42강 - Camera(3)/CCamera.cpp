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

		// 현재 카메라 위치를 이전 위치에서 목표 방향으로 보간한 새로운 위치로 업데이트
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
		// vLookDir.Normalize(): 방향 벡터를 단위 벡터로 변환.
		// m_fSpeed * fDT: 이번 프레임에서 카메라가 이동해야 할 거리.
		// 방향(단위 벡터) * 이동 거리 = 이동 벡터.
		// 이전 위치 + 이동 벡터 → 새로운 위치.
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution(); // 해상도.
	Vec2 vCenter = vResolution / 2; // 해상도 중심 좌표.

	// 화면 해상도의 중심과 카메라 위치의 차이를 구해 m_vDiff에 저장.
	m_vDiff = m_vCurLookAt - vCenter;

	// m_vPrevLookAt에 현재 프레임의 카메라 보정 위치를 저장하여 다음 프레임에서 보간 처리를 이어감.
	m_vPrevLookAt = m_vCurLookAt;
}
