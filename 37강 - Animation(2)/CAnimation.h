#pragma once

class CAnimator;
class CTexture;

// 애니메이션 한 프레임의 정보 구조체.
struct tAnimFrm
{
	Vec2  vLT;
	Vec2  vSlice;
	float fDuration;
};

class CAnimation
{
private:
	wstring			 m_strName;
	CAnimator* m_pAnimator;
	CTexture* m_pTex;   // 애니메이션이 사용하는 텍스쳐.
	vector<tAnimFrm> m_vecFrm; // 모든 프레임 정보.

public:
	const wstring& Getname() { return m_strName; }

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
