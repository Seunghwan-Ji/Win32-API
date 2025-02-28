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
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	// Texture �ε��ϱ�.
	// m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	CreateCollider(); // �浹 ���� ����.
	GetCollider()->SetOffsetPos(Vec2(0.f, 12.f)); // �浹 ���� ��ġ ����.
	GetCollider()->SetScale(Vec2(20.f, 40.f)); // �浹 ���� ������ ����.

	// Texture �ε��ϱ�.
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link_0.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f)
		, Vec2(60.f, 0.f), 0.08f, 10);
	GetAnimator()->Play(L"WALK_DOWN", true);

	// �ؽ��ĸ� ������Ʈ ��ġ���� ���ʿ� ��ġ.
	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
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

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos); // �θ� Ŭ������ ���� ��ǥ ����.

	GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	// ������Ʈ(�浹ü, etc...)�� �ִ� ��� ����.
	// component_render(_dc);

	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Plane", L"texture\\Player_A.bmp");

	Vec2 vPos = GetPos(); // ��ǥ �޾ƿ���.
	vPos = CCamera::GetInst()->GetRenderPos(vPos); // ������ ��ǥ�� ��ȯ.

	// �ؽ�ó ������ ����.
	float width = (float)pTex->Width();
	float height = (float)pTex->Height();

	// AlphaBlend �Լ��� ������ ���ڿ� �ִ� �ɼ��� ��ü.
	// ���� �������� Microsoft Learn ������ ���� �����.
	BLENDFUNCTION bf = {};

	// ���� ��� ���� �� �̹����� ���� ���� ������� ���� �����.
	bf.BlendOp = AC_SRC_OVER;

	// ������ �ʴ� �ʵ��̹Ƿ� �׻� 0���� ����.
	bf.BlendFlags = 0;
	
	// �ҽ� �̹��� ��ü�� ���Ե� ���� ä��(���� ����)�� ���.
	// ��, �ȼ����� �������� ������ ������ �� ����.
	bf.AlphaFormat = AC_SRC_ALPHA;

	// �ҽ� �̹����� ��ü ������ 255(���� ������)�� ����.
	// ��, �ҽ� �̹����� ��ü ���� ä�� ���� �����.
	bf.SourceConstantAlpha = 255;

	AlphaBlend(_dc
		// ������ ������ ���� ��ǥ �� ������.
		, int(vPos.x - width / 2.f)
		, int(vPos.y - height / 2.f)
		, int(width), int(height)
		// �ؽ�ó DC.
		, pTex->GetDC()
		// �ؽ�ó���� ���縦 ������ ��ǥ �� ������.
		, 0, 0
		, int(width), int(height)
		// �� ��Ĵ�� �ۼ��� ��ü�� �ִ� �� �Լ��� ������ �ɼ�.
		, bf);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}
