#pragma once
#include "CScene.h"

class CScene_Start : public CScene
{
public:
	virtual void Enter();
	virtual void Exit();
	// �̹� �θ��ʿ��� ���� �Լ��� �����߱� ������ virtual Ű���带 ������ �ʾƵ� ������,
	// �Ϲ� �Լ����� �θ�κ��� ��� ���� ���� �Լ�������, virtual Ű���带 �ٿ� ����Ѵ�.

public:
	CScene_Start();
	~CScene_Start();
};