#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*> m_mapAnim;  // 모든 애니메이션.
	CAnimation*				  m_pCurAnim; // 현재 재생중인 애니메이션.
	CObject*				  m_pOwner;   // Animator 소유 오브젝트.
	bool					  m_bRepeat;  // 애니메이션 반복 재생 여부.

public:
	CObject* GetObj() { return m_pOwner; }

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT
		, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);

	void update();
	void finalupdate(); // CAnimator 와 같은 컴포넌트는 update 대신 finalupdate 호출.
	void render(HDC _dc);

public:
	CAnimator();
	~CAnimator();
	friend class CObject;
};
