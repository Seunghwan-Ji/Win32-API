#include "CBtnUI.h"

CBtnUI::CBtnUI()
	: CUI(false)
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneInst(nullptr)
	, m_pSceneFunc(nullptr)
{
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}

void CBtnUI::MouseLbtnClicked()
{
	// 콜백 함수가 있는지 확인.
	if (nullptr != m_pFunc)
	{
		// 해당 함수 호출.
		m_pFunc(m_param1, m_param2);
	}

	// 객체와 콜백 멤버 함수가 있는지 확인.
	if (m_pSceneInst && m_pSceneFunc)
	{
		// 해당 멤버 함수 호출
		((*m_pSceneInst).*m_pSceneFunc)();
		// ((*객체주소).*함수주소)(매개변수(void))
	}
}

void CBtnUI::SetClikedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
{
	m_pSceneFunc = _pSceneFunc;
	m_pSceneInst = _pScene;
}