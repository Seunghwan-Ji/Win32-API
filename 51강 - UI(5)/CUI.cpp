#include "CUI.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "SelectGDI.h"

CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCamAffected(false)
	, m_bMouseOn(false)
{
}

CUI::CUI(const CUI& _origin)
	// �ڽ��ʿ��� ���� ������ ���� �������� ���, ���ο��� �θ����� ���� �����ڸ�
	// ��������� ��Ī���� ������, �θ����� �⺻ ���� �����ڰ� ȣ��Ǵ� �Ϳ� �����ؾ� �Ѵ�.
	: CObject(_origin)
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
	// �ڽ� UI ����.
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
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

	// UI ���콺 üũ
	MouseOnCheck();

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

	// ī�޶� ������ �޴� UI �̸�, ������ ��ǥ�� ��ȯ.
	if (m_bCamAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	// UI �� ���� �������� �ð������� Ȯ��.
	if (m_bLbtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);

		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}

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

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	// ���콺�� UI ���ο� �ִ��� üũ.
	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

// �ߴ��� �ɰ� ���콺�� Ŭ���ϰ� ���鼭 �� �Լ��� � UI �� �������� Ȯ��.
void CUI::MouseOn()
{
	wstring strName = this->GetName();
}

void CUI::MouseLbtnDown()
{
	wstring strName = this->GetName();
}

void CUI::MouseLbtnUp()
{
	wstring strName = this->GetName();
}

void CUI::MouseLbtnClicked()
{
	wstring strName = this->GetName();
}
