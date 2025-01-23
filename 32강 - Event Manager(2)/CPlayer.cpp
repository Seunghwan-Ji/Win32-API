#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	// Texture �ε��ϱ�.
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	CreateCollider(); // �浹 ���� ����.
	GetCollider()->SetOffsetPos(Vec2(0.f, 12.f)); // �浹 ���� ��ġ ����.
	GetCollider()->SetScale(Vec2(20.f, 40.f)); // �浹 ���� ������ ����.
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	Vec2 vPos = GetPos(); // �θ� Ŭ������ ���� ��ǥ �޾ƿ���.

	if (KEY_HOLD(KEY::UP))
	{
		vPos.y -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY::DOWN))
	{
		vPos.y += 200.f * fDT;
	}

	if (KEY_HOLD(KEY::LEFT))
	{
		vPos.x -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY::RIGHT))
	{
		vPos.x += 200.f * fDT;
	}

	if (KEY_TAP(KEY::A))
	{
		CreateMissile();
	}

	SetPos(vPos); // �θ� Ŭ������ ���� ��ǥ ����.
}

void CPlayer::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();

	TransparentBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()    // �ҽ� �̹����� ��Ʈ���� �����ϰ� �ִ� DC.
		, 0, 0			     // �ҽ� �̹������� ������ �κ��� ���� ��ǥ.
		, iWidth, iHeight    // ���� ��ǥ�κ��� ������ �ʺ�� ����.
		, RGB(255, 0, 255)); // �ҽ� �̹������� �������� ���� �ȼ� ����.(���� ó���� ����)

	// ������Ʈ(�浹ü, etc...)�� �ִ� ��� ����.
	component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}
