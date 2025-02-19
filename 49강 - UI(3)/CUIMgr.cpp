#include "pch.h"
#include "CUIMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyMgr.h"

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		// �θ� UI ����, �ڽ� UI �� �� ���� Ÿ���� �� UI �� �����´�.
		pUI = GetTargetedUI(pUI);

		if (nullptr != pUI)
		{
			pUI->MouseOn();

			if (bLbtnTap)
			{ // ���콺 ��ư�� ���� ����.
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if (bLbtnAway)
			{ // ���콺 ��ư�� �� ����.
				pUI->MouseLbtnUp();

				// ������ ��ư�� ���� ���¿��� ���.
				if (pUI->m_bLbtnDown)
				{
					// UI �� Ŭ���� ������ �Ǵ�.
					pUI->MouseLbtnClicked();
				}

				pUI->m_bLbtnDown = false;
			}
		}
	}
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	// 1. �θ� UI ����, ��� �ڽĵ��� �˻��Ѵ�.
	// 2. Ÿ�� UI �� ��, �� �켱 ������ ���� ������ �� ���� ������ �ڽ� UI.

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	CUI* pTargetUI = nullptr;

	// ���� ���� ������ ����ǹǷ�, �Ź� ���� ������ ��ü�� �����ϴ� �� ����, ���� ������ ������ �д�
	static list<CUI*> queue; // ����Ʈ�� ť ó�� ���.
	static vector<CUI*> vecNoneTarget; // Ÿ���� ���� ���� UI ����.

	// ���빰 ����.
	queue.clear();
	vecNoneTarget.clear();

	// ť�� UI �߰�.
	queue.push_back(_pParentUI);

	// ť�� ����� ������ �ݺ�.
	while (!queue.empty())
	{
		// ť���� ������(UI) �ϳ� ������
		CUI* pUI = queue.front(); // �� �� ������ ������.
		queue.pop_front(); // ���� �����ʹ� ť���� �����.

		// ť���� ������ UI �� TargetUI ���� Ȯ��.(UI ���ο� ���콺�� �÷��� �ִ� ���.)
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				// nullptr �� �ƴ� ���� ������ Ÿ���̾��� UI �̴�.
				// �� ���� ������ UI �� Ÿ���� �� �����̹Ƿ�,
				// ���� UI �� ��Ÿ�� ���Ϳ� ����ִ´�.
				vecNoneTarget.push_back(pTargetUI);
			}

			// Ÿ�� UI ����.(���� ���� ������ UI �� ���ŵ�.)
			pTargetUI = pUI;
		}
		else
		{
			// Ÿ���� ���� ���� UI �� ���� ��Ƶд�.
			vecNoneTarget.push_back(pUI);
		}

		// ���� UI �� �ڽ� UI ���� ť�� �߰��Ͽ� ���� �������� �˻縦 ��� ����.
		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	// UI �ٱ����� ��ư�� ����, ���� ���¸� �����Ѵ�.
	// Ÿ�� UI �� ���ؼ�, update �Լ����� ó��.
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	// ���� Ÿ�� UI ��ȯ.
	return pTargetUI;
}
