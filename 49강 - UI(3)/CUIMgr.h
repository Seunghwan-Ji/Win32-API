#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:

public:
	void update();

private:
	// �θ� UI ���� ������ Ÿ���õ� UI �� ã�Ƽ� ��ȯ�ϴ� �Լ�.
	CUI* GetTargetedUI(CUI* _pParentUI);
};

