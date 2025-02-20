#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	CUI* m_pFocusedUI;

public:
	void update();

	void SetFocusedUI(CUI* _pUI); // Ư�� UI �� ������ ��Ŀ�� ���ִ� �Լ�.

private:
	CUI* GetFocusedUI(); // �θ� UI �� ��, ������ Ÿ���õ� UI �� ã�Ƽ� ��ȯ�ϴ� �Լ�.
	CUI* GetTargetedUI(CUI* _pParentUI);
};

