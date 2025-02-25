#pragma once

#include "CUI.h"
#include "CScene.h"
#include "CObject.h"

// 함수 포인터.
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
// 특정 버튼 입력시, 그 버튼에 맞는 기능을 하는 함수의 주소를 받아 호출시키기 위한 용도.

// 인자와 반환 타입이 없어야 하고, CScene(자식 포함) 의 멤버 함수의 주소만 받을 수 있는 함수 포인터.
typedef void(CScene::*SCENE_MEMFUNC)(void);

// CObject(자식 포함) 멤버 함수의 주소를 받는 함수 포인터.
typedef void(CObject::*OBJECT_MEMFUNC)(void);

class CBtnUI :
    public CUI
{
private:
    BTN_FUNC      m_pFunc; // 호출할 전역 함수.
    DWORD_PTR     m_param1; // 매개변수1.
    DWORD_PTR     m_param2; // 매개변수2.

    SCENE_MEMFUNC m_pSceneFunc; // 호출할 멤버 함수.
    CScene*       m_pSceneInst; // 호출할 객체.

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

    // 함수 포인터 오버로딩.(특정 객체의 멤버 함수 포인터)
    void SetClikedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

