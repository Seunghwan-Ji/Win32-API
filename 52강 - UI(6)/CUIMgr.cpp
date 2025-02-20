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
	// 1. FocusedUI 확인.
	m_pFocusedUI = GetFocusedUI();

	// 포커싱 UI 가 없다면 함수 종료.
	if (!m_pFocusedUI)
		return;

	// 2. FocusedUI 내에서, 부모 UI 포함, 자식 UI 들 중 실제 타겟팅 된 UI 를 가져온다.
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);
	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{ // 마우스 버튼을 누른 상태.
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{ // 마우스 버튼을 뗀 상태.
			pTargetUI->MouseLbtnUp();

			// 이전에 버튼을 누른 상태였을 경우.
			if (pTargetUI->m_bLbtnDown)
			{
				// UI 를 클릭한 것으로 판단.
				pTargetUI->MouseLbtnClicked();
			}

			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	// 인자 값이 이미 포커싱 중인 UI 이거나, 모든 UI 의 포커싱을 해제할 의도인 nullptr 인 경우.
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		// 통합 수행문.
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	// 포커싱 요청한 UI 를 소유한 이터레이터 찾기.
	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	// UI 순서 변경.
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 UI 를 받아두고 변경되었는지 확인한다.
	CUI* pFocusedUI = m_pFocusedUI;

	// 마우스 왼쪽 클릭이 발생하지 않았다면, 포커싱이 변경되지 않으므로 그대로 반환.
	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// 왼쪽 버튼 TAP 이 발생했다는 전제.
	vector<CObject*>::iterator targetIter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		// 타겟 UI 를 소유한 이터레이터를 찾아서 갱신.
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}

	// targetIter 가 end 이터레이터로 유지 되었다면,
	// 타겟된 UI 가 없어서 포커싱 대상이 없으므로 nullptr 반환.
	if (vecUI.end() == targetIter)
	{
		return nullptr;
	}

	// 최종 타겟 UI 를 포커싱 UI 로 결정.
	pFocusedUI = (CUI*)*targetIter;

	// 벡터 내에서 맨 뒤로 순번 교체.
	// 포커싱 UI 는 가장 마지막에 렌더링 되어야 하므로, 지우고 뒤에 추가한다.
	vecUI.erase(targetIter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
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
