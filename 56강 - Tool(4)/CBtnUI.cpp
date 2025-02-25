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
	// �ݹ� �Լ��� �ִ��� Ȯ��.
	if (nullptr != m_pFunc)
	{
		// �ش� �Լ� ȣ��.
		m_pFunc(m_param1, m_param2);
	}

	// ��ü�� �ݹ� ��� �Լ��� �ִ��� Ȯ��.
	if (m_pSceneInst && m_pSceneFunc)
	{
		// �ش� ��� �Լ� ȣ��
		((*m_pSceneInst).*m_pSceneFunc)();
		// ((*��ü�ּ�).*�Լ��ּ�)(�Ű�����(void))
	}
}

void CBtnUI::SetClikedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
{
	m_pSceneFunc = _pSceneFunc;
	m_pSceneInst = _pScene;
}