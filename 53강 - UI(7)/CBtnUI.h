#pragma once

#include "CUI.h"

// �Լ� ������.
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
// Ư�� ��ư �Է½�, �� ��ư�� �´� ����� �ϴ� �Լ��� �ּҸ� �޾� ȣ���Ű�� ���� �뵵.
// *BTN_FUNC: �Լ��� �ּҸ� ����. �Լ� ������ ����.
// DWORD_PTR: �Ű� ������ �ּҸ� ����. Ÿ�� ��ü�� �����͸� ������ �� ����.
//            Win32 API ���� ������ ��ȣ ���� ������ Ÿ��.

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

    // �ݹ� �Լ�, ȣ���� �Լ��� ������.
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

