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
	Vec2 vLookDir = m_vLookAt - m_PrevLookAt;

	m_vCurLookAt = m_PrevLookAt + vLookDir.Normalize() * 500.f * fDT;

	Vec2 vResolution = CCore::GetInst()->GetResolution(); // 해상도.
	Vec2 vCenter = vResolution / 2; // 해상도 중심 좌표.

	m_vDiff = m_vCurLookAt - vCenter;
	m_PrevLookAt = m_vCurLookAt;
}
