#include "CUI.h"

CUI::CUI()
	: m_pParentUI(nullptr)
{
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI); // �ڽ� UI ���� ����.
}

void CUI::update()
{
	update_child();
}

void CUI::finalupdate()
{
	CObject::finalupdate(); // �ִϸ��̼��� ������ UI �� ���� ȣ��.

	// UI �� ���� ��ǥ�� ���Ѵ�.
	// ���� ��ǥ = �θ� ��ǥ + �θ�κ��� ������� �Ÿ�.
	m_vFinalPos = GetPos(); // �θ� ���� UI �� ���� ��ǥ.

	// �θ� ���� ���.
	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos; // �θ��� ��ġ�� ���Ѵ�.
	}

	finalupdate_child();
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, int(vPos.x)
		, int(vPos.y)
		, int(vPos.x + vScale.x)
		, int(vPos.y + vScale.y));

	// �θ� UI �� �������� ������, �ڽ� UI ������.
	render_child(_dc);
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}