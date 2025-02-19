#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:

public:
	void update();

private:
	// 부모 UI 에서 실제로 타게팅된 UI 를 찾아서 반환하는 함수.
	CUI* GetTargetedUI(CUI* _pParentUI);
};

