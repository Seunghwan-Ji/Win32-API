#pragma once

class CObject;
class CAnimation;

class CAnimator
{
private:
	map<wstring, CAnimation*> m_mapAnim; // �ִϸ��̼ǵ��� �����ϴ� ��� ����.
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

