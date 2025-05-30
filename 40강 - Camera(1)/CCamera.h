#pragma once

class CObject;

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2	 m_vLookAt;    // 카메라가 보는 위치.
	CObject* m_pTargetObj; // 카메라가 추적하는 오브젝트.

	Vec2	 m_vDiff;      // 해상도 중심 위치와, 카메라 LookAt 간의 차이 값.

public:
	void SetLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; } // 오브젝트를 렌더링할 좌표.

public:
	void update();

private:
	void CalDiff(); // m_vDiff 값을 계산하는 함수.
};

