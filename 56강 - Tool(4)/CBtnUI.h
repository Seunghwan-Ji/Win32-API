#pragma once

#include "CUI.h"
#include "CScene.h"
#include "CObject.h"

// �Լ� ������.
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
// Ư�� ��ư �Է½�, �� ��ư�� �´� ����� �ϴ� �Լ��� �ּҸ� �޾� ȣ���Ű�� ���� �뵵.

// ���ڿ� ��ȯ Ÿ���� ����� �ϰ�, CScene(�ڽ� ����) �� ��� �Լ��� �ּҸ� ���� �� �ִ� �Լ� ������.
typedef void(CScene::*SCENE_MEMFUNC)(void);

// CObject(�ڽ� ����) ��� �Լ��� �ּҸ� �޴� �Լ� ������.
typedef void(CObject::*OBJECT_MEMFUNC)(void);

class CBtnUI :
    public CUI
{
private:
    BTN_FUNC      m_pFunc; // ȣ���� ���� �Լ�.
    DWORD_PTR     m_param1; // �Ű�����1.
    DWORD_PTR     m_param2; // �Ű�����2.

    SCENE_MEMFUNC m_pSceneFunc; // ȣ���� ��� �Լ�.
    CScene*       m_pSceneInst; // ȣ���� ��ü.

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    // �ݹ� �Լ�, ȣ���� �Լ��� ������.
    void SetClikedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    // �Լ� ������ �����ε�.(Ư�� ��ü�� ��� �Լ� ������)
    void SetClikedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

