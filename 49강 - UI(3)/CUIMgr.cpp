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

		// 부모 UI 포함, 자식 UI 들 중 실제 타겟팅 된 UI 를 가져온다.
		pUI = GetTargetedUI(pUI);

		if (nullptr != pUI)
		{
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
	}
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	// 1. 부모 UI 포함, 모든 자식들을 검사한다.
	// 2. 타겟 UI 들 중, 더 우선 순위가 높은 기준은 더 낮은 계층의 자식 UI.

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	CUI* pTargetUI = nullptr;

	// 자주 쓰일 것으로 예상되므로, 매번 지역 변수로 객체를 생성하는 것 보단, 정적 변수로 생성해 둔다
	static list<CUI*> queue; // 리스트를 큐 처럼 사용.
	static vector<CUI*> vecNoneTarget; // 타겟이 되지 않은 UI 모음.

	// 내용물 비우기.
	queue.clear();
	vecNoneTarget.clear();

	// 큐에 UI 추가.
	queue.push_back(_pParentUI);

	// 큐가 비워질 때까지 반복.
	while (!queue.empty())
	{
		// 큐에서 데이터(UI) 하나 꺼내기
		CUI* pUI = queue.front(); // 맨 앞 데이터 꺼내기.
		queue.pop_front(); // 꺼낸 데이터는 큐에서 지우기.

		// 큐에서 꺼내온 UI 가 TargetUI 인지 확인.(UI 내부에 마우스가 올려져 있는 경우.)
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				// nullptr 이 아닌 경우는 이전에 타겟이었던 UI 이다.
				// 더 하위 계층늬 UI 가 타겟이 된 상태이므로,
				// 이전 UI 를 논타겟 벡터에 집어넣는다.
				vecNoneTarget.push_back(pTargetUI);
			}

			// 타겟 UI 갱신.(점점 하위 계층의 UI 로 갱신됨.)
			pTargetUI = pUI;
		}
		else
		{
			// 타겟이 되지 않은 UI 는 따로 모아둔다.
			vecNoneTarget.push_back(pUI);
		}

		// 꺼낸 UI 의 자식 UI 들을 큐에 추가하여 다음 루프에서 검사를 계속 진행.
		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	// UI 바깥에서 버튼을 떼면, 누른 상태를 해제한다.
	// 타겟 UI 에 대해선, update 함수에서 처리.
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	// 최종 타겟 UI 반환.
	return pTargetUI;
}
