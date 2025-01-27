#pragma once

class CObject;
class CAnimation;

class CAnimator
{
private:
	map<wstring, CAnimation*> m_mapAnim; // 애니메이션들을 저장하는 멤버 변수.
	CObject* m_pOwner;

public:
	void CreateAnimation();
	void FindAnimation();
	void Play();

public:
	CAnimator();
	~CAnimator();
	friend class CObject;
};

