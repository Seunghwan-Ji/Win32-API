#include "pch.h"
#include "CUIMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	// 1. FocusedUI Ȯ��.
	m_pFocusedUI = GetFocusedUI();

	// ��Ŀ�� UI �� ���ٸ� �Լ� ����.
	if (!m_pFocusedUI)
		return;

	// 2. FocusedUI ������, �θ� UI ����, �ڽ� UI �� �� ���� Ÿ���� �� UI �� �����´�.
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);
	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{ // ���콺 ��ư�� ���� ����.
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{ // ���콺 ��ư�� �� ����.
			pTargetUI->MouseLbtnUp();

			// ������ ��ư�� ���� ���¿��� ���.
			if (pTargetUI->m_bLbtnDown)
			{
				// UI �� Ŭ���� ������ �Ǵ�.
				pTargetUI->MouseLbtnClicked();
			}

			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	// ���� ���� �̹� ��Ŀ�� ���� UI �̰ų�, ��� UI �� ��Ŀ���� ������ �ǵ��� nullptr �� ���.
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		// ���� ���๮.
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	// ��Ŀ�� ��û�� UI �� ������ ���ͷ����� ã��.
	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	// UI ���� ����.
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// ���� ��Ŀ�� UI �� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	CUI* pFocusedUI = m_pFocusedUI;

	// ���콺 ���� Ŭ���� �߻����� �ʾҴٸ�, ��Ŀ���� ������� �����Ƿ� �״�� ��ȯ.
	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// ���� ��ư TAP �� �߻��ߴٴ� ����.
	vector<CObject*>::iterator targetIter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		// Ÿ�� UI �� ������ ���ͷ����͸� ã�Ƽ� ����.
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}

	// targetIter �� end ���ͷ����ͷ� ���� �Ǿ��ٸ�,
	// Ÿ�ٵ� UI �� ��� ��Ŀ�� ����� �����Ƿ� nullptr ��ȯ.
	if (vecUI.end() == targetIter)
	{
		return nullptr;
	}

	// ���� Ÿ�� UI �� ��Ŀ�� UI �� ����.
	pFocusedUI = (CUI*)*targetIter;

	// ���� ������ �� �ڷ� ���� ��ü.
	// ��Ŀ�� UI �� ���� �������� ������ �Ǿ�� �ϹǷ�, ����� �ڿ� �߰��Ѵ�.
	vecUI.erase(targetIter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
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
