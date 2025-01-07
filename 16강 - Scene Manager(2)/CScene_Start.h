#pragma once
#include "CScene.h"

class CScene_Start : public CScene
{
public:
	virtual void Enter();
	virtual void Exit();
	// 이미 부모쪽에서 가상 함수를 정의했기 때문에 virtual 키워드를 붙이지 않아도 되지만,
	// 일반 함수인지 부모로부터 상속 받은 가상 함수인지를, virtual 키워드를 붙여 명시한다.

public:
	CScene_Start();
	~CScene_Start();
};