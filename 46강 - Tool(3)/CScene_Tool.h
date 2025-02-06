#pragma once

#include "CScene.h"

class CScene_Tool :
    public CScene
{
private:

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    void SetTileIdx(); // 마우스로 클릭한 타일의 인덱스를 증가시켜 타일을 변경시키는 함수.

public:
    CScene_Tool();
    ~CScene_Tool();
};

