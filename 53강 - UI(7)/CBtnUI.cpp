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
	// �ݹ� �Լ��� �ִ��� Ȯ��.
	if (nullptr != m_pFunc)
	{
		// �ش� �Լ� ȣ��.
		m_pFunc(m_param1, m_param2);
	}
}
