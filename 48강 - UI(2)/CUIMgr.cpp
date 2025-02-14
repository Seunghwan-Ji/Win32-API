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
	const vector<CObject*>& vecUI  = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		if (pUI->IsMouseOn())
		{ // ���콺�� UI �� ������ ����.
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
		else
		{
			// UI �ٱ����� ��ư�� ���� ���.
			if (bLbtnAway)
			{
				pUI->m_bLbtnDown = false;
			}
		}
	}
}
