#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2	 m_vLookAt;     // 카메라가 최종적으로 바라봐야 할 위치.(목표 위치)
	Vec2     m_vCurLookAt;  // 카메라가 목표 지점까지 부드럽게 이동하기 위해 계산된 보정된 현재 위치.
	Vec2	 m_vPrevLookAt; // 카메라가 보는 이전 프레임 위치.
	CObject* m_pTargetObj;  // 카메라가 추적하는 오브젝트.
	Vec2	 m_vDiff;       // 해상도 중심 위치와, 카메라 LookAt 간의 차이 값.
	float	 m_fTime;	    // 타겟을 따라가는데 걸리는 시간.
	float	 m_fSpeed;	    // 타겟을 따라가는 속도.
	float    m_fAccTime;    // 누적 시간.
	float    m_fEffectDuration; // 효과 최대 진행 시간.
	float    m_fCurTime;        // 카메라 효과 현재 진행된 시간.

	CAM_EFFECT m_eEffect;   // 카메라 효과.

	CTexture* m_pVeilTex;   // 카메라 가림막 텍스처(검은색으로)

public:
	void SetLookAt(Vec2 _vLook)
	{
		m_vLookAt = _vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length(); // 거리 차이 길이 계산.
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}

	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetLookAt() { return m_vCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; } // 오브젝트를 렌더링할 좌표.

	void FadeIn();
	void FadeOut(float _fDuration)
	{
		m_eEffect = CAM_EFFECT::FADE_OUT;
		m_fEffectDuration = _fDuration;

		if (0.f == m_fEffectDuration)
			assert(nullptr);
	}
	
	// 렌더링 좌표의 실제 좌표 반환 함수.
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

public:
	void init();
	void update();
	void render(HDC _dc);

private:
	void CalDiff(); // m_vDiff 값을 계산하는 함수.
};

