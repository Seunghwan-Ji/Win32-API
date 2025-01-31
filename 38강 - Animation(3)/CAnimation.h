#pragma once

class CAnimator;
class CTexture;

// 애니메이션 한 프레임의 정보 구조체.
struct tAnimFrm
{
	Vec2  vLT;       // 좌상단 좌표.
	Vec2  vSlice;	 // 간격(너비, 높이).
	float fDuration; // 프레임 지속 시간.
};

class CAnimation
{
private:
	wstring			 m_strName;
	CAnimator* m_pAnimator;
	CTexture* m_pTex;     // 애니메이션이 사용하는 텍스쳐.
	vector<tAnimFrm> m_vecFrm;   // 모든 프레임 정보.
	int		         m_iCurFrm;  // 현재 프레임.
	float			 m_fAccTime; // 시간 누적.

	bool			 m_bFinish;  // 재생 끝에 도달 여부.

public:
	const wstring& Getname() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void update();
	void render(HDC _dc);
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};
