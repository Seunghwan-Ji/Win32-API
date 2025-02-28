#pragma once

class CObject;
class CTexture;

// ī�޶� ȿ�� ����.
enum class CAM_EFFECT
{
	FADE_IN,  // ���� ������� ȿ��.
	FADE_OUT, // ���� ��ο����� ȿ��.
	NONE,
};

// ī�޶� ȿ�� ���� ����ü.
struct tCamEffect
{
	CAM_EFFECT eEffect;     // ī�޶� ȿ��.
	float	   fDuration; // ȿ�� �ִ� ���� �ð�.
	float      fCurTime;  // ī�޶� ȿ�� ���� ����� �ð�.
};

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2	         m_vLookAt;       // ī�޶� ���������� �ٶ���� �� ��ġ.(��ǥ ��ġ)
	Vec2             m_vCurLookAt;    // ī�޶� ��ǥ �������� �ε巴�� �̵��ϱ� ���� ���� ������ ���� ��ġ.
	Vec2	         m_vPrevLookAt;   // ī�޶� ���� ���� ������ ��ġ.
	CObject*         m_pTargetObj;    // ī�޶� �����ϴ� ������Ʈ.
	Vec2	         m_vDiff;         // �ػ� �߽� ��ġ��, ī�޶� LookAt ���� ���� ��.
	float	         m_fTime;	      // Ÿ���� ���󰡴µ� �ɸ��� �ð�.
	float	         m_fSpeed;	      // Ÿ���� ���󰡴� �ӵ�.
	float            m_fAccTime;      // ���� �ð�.

	list<tCamEffect> m_listCamEffect; // ī�޶� ȿ�� ����ü ����Ʈ.
	CTexture*        m_pVeilTex;	  // ī�޶� ������ �ؽ�ó(����������)

public:
	void SetLookAt(Vec2 _vLook)
	{
		m_vLookAt = _vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length(); // �Ÿ� ���� ���� ���.
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}

	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetLookAt() { return m_vCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; } // ������Ʈ�� �������� ��ǥ.

	// ī�޶� ȿ�� �� ���� �ð� ���� �Լ�.
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
	
	// ������ ��ǥ�� ���� ��ǥ ��ȯ �Լ�.
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

public:
	void init();
	void update();
	void render(HDC _dc);

private:
	void CalDiff(); // m_vDiff ���� ����ϴ� �Լ�.
};

