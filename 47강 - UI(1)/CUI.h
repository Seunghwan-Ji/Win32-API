#pragma once
#include "CObject.h"

// UI �� ���� ������ ����.

class CUI :
    public CObject
{
private:
    vector<CUI*> m_vecChildUI; // �ڽ� UI �� ��� ����.
    CUI*         m_pParentUI;  // �θ� UI.

    Vec2         m_vFinalPos;  // UI ���� ��ġ.

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }

    CUI* GetParent() { return m_pParentUI; } // �θ� UI ��ȯ �Լ�.

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
    
    CLONE(CUI);

public:
    CUI();
    ~CUI();
};

