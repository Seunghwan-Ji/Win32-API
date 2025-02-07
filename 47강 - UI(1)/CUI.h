#pragma once
#include "CObject.h"

// UI 는 계층 구조로 설계.

class CUI :
    public CObject
{
private:
    vector<CUI*> m_vecChildUI; // 자식 UI 를 담는 벡터.
    CUI*         m_pParentUI;  // 부모 UI.

    Vec2         m_vFinalPos;  // UI 최종 위치.

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }

    CUI* GetParent() { return m_pParentUI; } // 부모 UI 반환 함수.

    // 자식 UI 추가 함수.
    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }

public:
    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);

private:
    void update_child();        // 자식 UI 업데이트 함수.
    void finalupdate_child();
    void render_child(HDC _dc); // 자식 UI 렌더링 함수.
    
    CLONE(CUI);

public:
    CUI();
    ~CUI();
};

