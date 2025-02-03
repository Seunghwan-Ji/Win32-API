#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"

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

	// 화면 중앙 좌표와 카메라 LookAt 좌표간의 차이값 계산.
	CalDiff();
}

void CCamera::CalDiff()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution(); // 해상도.
	Vec2 vCenter = vResolution / 2; // 해상도 중심 좌표.

	m_vDiff = m_vLookAt - vCenter;
}
