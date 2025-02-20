#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	CUI* m_pFocusedUI;

public:
	void update();

	void SetFocusedUI(CUI* _pUI); // 특정 UI 를 강제로 포커싱 해주는 함수.

private:
	CUI* GetFocusedUI(); // 부모 UI 들 중, 실제로 타게팅된 UI 를 찾아서 반환하는 함수.
	CUI* GetTargetedUI(CUI* _pParentUI);
};

