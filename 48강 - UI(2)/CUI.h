#pragma once
#include "CObject.h"

// UI �� ���� ������ ����.

class CUI :
    public CObject
{
private:
    vector<CUI*> m_vecChildUI;   // �ڽ� UI �� ��� ����.
    CUI*         m_pParentUI;    // �θ� UI.
    Vec2         m_vFinalPos;    // UI ���� ��ġ.

    bool         m_bCamAffected; // UI �� ī�޶� ������ �޴��� ����.
    bool         m_bMouseOn;     // UI ���� ���콺�� �ִ��� ����.
    bool         m_bLbtnDown;    // UI �� ���콺 ���� ��ư�� �������� �ִ��� ����.

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    CUI* GetParent() { return m_pParentUI; } // �θ� UI ��ȯ �Լ�.
    bool IsMouseOn() { return m_bMouseOn; } // ���콺�� UI ���ο� �ִ��� ���� ��ȯ.

    // �ڽ� UI �߰� �Լ�.
    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }

public:
    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);

private:
    void update_child();        // �ڽ� UI ������Ʈ �Լ�.
    void finalupdate_child();
    void render_child(HDC _dc); // �ڽ� UI ������ �Լ�.

    void MouseOnCheck();

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();
    
    CLONE(CUI);

public:
    CUI(bool _bCamAff); // �ڽ� UI �� ī�޶� ������ �޴��� ������ ����� �ʰ� ���� �� �� �ְ�,
                        // �⺻ ������ ��� ���� ������ �޴� �����ڷ� ���Ѵ�.
    virtual ~CUI();

    friend class CUIMgr;
};

