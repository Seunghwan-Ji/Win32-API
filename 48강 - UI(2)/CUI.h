#pragma once
#include "CObject.h"

// UI 는 계층 구조로 설계.

class CUI :
    public CObject
{
private:
    vector<CUI*> m_vecChildUI;   // 자식 UI 를 담는 벡터.
    CUI*         m_pParentUI;    // 부모 UI.
    Vec2         m_vFinalPos;    // UI 최종 위치.

    bool         m_bCamAffected; // UI 가 카메라에 영향을 받는지 유무.
    bool         m_bMouseOn;     // UI 위에 마우스가 있는지 유무.
    bool         m_bLbtnDown;    // UI 에 마우스 왼쪽 버튼이 눌린적이 있는지 유무.

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    CUI* GetParent() { return m_pParentUI; } // 부모 UI 반환 함수.
    bool IsMouseOn() { return m_bMouseOn; } // 마우스가 UI 내부에 있는지 여부 반환.

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

    void MouseOnCheck();

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();
    
    CLONE(CUI);

public:
    CUI(bool _bCamAff); // 자식 UI 가 카메라에 영향을 받는지 유무를 까먹지 않고 기입 할 수 있게,
                        // 기본 생성자 대신 인자 정보를 받는 생성자로 정한다.
    virtual ~CUI();

    friend class CUIMgr;
};

