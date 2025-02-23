#pragma once

#include "CUI.h"

// 함수 포인터.
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
// 특정 버튼 입력시, 그 버튼에 맞는 기능을 하는 함수의 주소를 받아 호출시키기 위한 용도.
// *BTN_FUNC: 함수의 주소를 받음. 함수 포인터 문법.
// DWORD_PTR: 매개 변수의 주소를 받음. 타입 자체가 포인터를 저장할 수 있음.
//            Win32 API 에서 정의한 부호 없는 정수형 타입.

class CBtnUI :
    public CUI
{
private:
    BTN_FUNC  m_pFunc;
    DWORD_PTR m_param1;
    DWORD_PTR m_param2;

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    // 콜백 함수, 호출할 함수를 세팅함.
    void SetClikedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

