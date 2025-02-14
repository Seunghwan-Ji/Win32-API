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
		{ // 마우스가 UI 에 진입한 상태.
			pUI->MouseOn();

			if (bLbtnTap)
			{ // 마우스 버튼을 누른 상태.
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if (bLbtnAway)
			{ // 마우스 버튼을 뗀 상태.
				pUI->MouseLbtnUp();

				// 이전에 버튼을 누른 상태였을 경우.
				if (pUI->m_bLbtnDown)
				{
					// UI 를 클릭한 것으로 판단.
					pUI->MouseLbtnClicked();
				}

				pUI->m_bLbtnDown = false;
			}
		}
		else
		{
			// UI 바깥에서 버튼을 뗐을 경우.
			if (bLbtnAway)
			{
				pUI->m_bLbtnDown = false;
			}
		}
	}
}
