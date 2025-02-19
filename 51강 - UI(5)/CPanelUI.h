#pragma once

#include "CUI.h"

class CPanelUI :
    public CUI
{
private:
    Vec2 m_vDragStart; // UI 드래그 시점의 마우스 좌표.

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();

    CLONE(CPanelUI);

public:
    CPanelUI();
    ~CPanelUI();
};

