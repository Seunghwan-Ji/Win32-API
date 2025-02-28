#pragma once

class CObject;
class CTexture;

// 카메라 효과 종류.
enum class CAM_EFFECT
{
	FADE_IN,  // 점점 밝아지는 효과.
	FADE_OUT, // 점점 어두워지는 효과.
	NONE,
};

// 카메라 효과 정보 구조체.
struct tCamEffect
{
	CAM_EFFECT eEffect;     // 카메라 효과.
	float	   fDuration; // 효과 최대 진행 시간.
	float      fCurTime;  // 카메라 효과 현재 진행된 시간.
};

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2	         m_vLookAt;       // 카메라가 최종적으로 바라봐야 할 위치.(목표 위치)
	Vec2             m_vCurLookAt;    // 카메라가 목표 지점까지 부드럽게 이동하기 위해 계산된 보정된 현재 위치.
	Vec2	         m_vPrevLookAt;   // 카메라가 보는 이전 프레임 위치.
	CObject*         m_pTargetObj;    // 카메라가 추적하는 오브젝트.
	Vec2	         m_vDiff;         // 해상도 중심 위치와, 카메라 LookAt 간의 차이 값.
	float	         m_fTime;	      // 타겟을 따라가는데 걸리는 시간.
	float	         m_fSpeed;	      // 타겟을 따라가는 속도.
	float            m_fAccTime;      // 누적 시간.

	list<tCamEffect> m_listCamEffect; // 카메라 효과 구조체 리스트.
	CTexture*        m_pVeilTex;	  // 카메라 가림막 텍스처(검은색으로)

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

	// 카메라 효과 및 지속 시간 적용 함수.
	void FadeIn(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (0.f == _fDuration)
			assert(nullptr);
	}

	void FadeOut(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (0.f == _fDuration)
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

