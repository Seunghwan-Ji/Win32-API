#include "CBtnUI.h"

CBtnUI::CBtnUI()
	: CUI(false)
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
}
