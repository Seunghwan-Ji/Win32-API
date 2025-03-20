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
#include "CRigidBody.h"

CPlayer::CPlayer()
	: m_eCurState(PLAYER_STATE::IDLE)
	, m_iDir(1)
{
	// Texture 로딩하기.
	// m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	CreateCollider(); // 충돌 영역 생성.
	GetCollider()->SetOffsetPos(Vec2(0.f, 12.f)); // 충돌 영역 위치 조정.
	GetCollider()->SetScale(Vec2(20.f, 40.f)); // 충돌 영역 사이즈 조정.

	CreateRigidBody(); // 강체 기능 생성.

	// Texture 로딩하기.
	CTexture* pLeftTex = CResMgr::GetInst()->LoadTexture(L"PlayerLeft", L"texture\\Player01_L.bmp");
	CTexture* pRightTex = CResMgr::GetInst()->LoadTexture(L"PlayerRight", L"texture\\Player01_R.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pLeftTex, Vec2(0.f, 0.f), Vec2(100.f, 100.f)
		, Vec2(100.f, 0.f), 0.2f, 9);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pRightTex, Vec2(0.f, 0.f), Vec2(100.f, 100.f)
		, Vec2(100.f, 0.f), 0.2f, 9);

	GetAnimator()->CreateAnimation(L"WALK_LEFT", pLeftTex, Vec2(0.f, 100.f), Vec2(100.f, 100.f)
		, Vec2(100.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pRightTex, Vec2(0.f, 100.f), Vec2(100.f, 100.f)
		, Vec2(100.f, 0.f), 0.2f, 4);

	GetAnimator()->Play(L"IDLE_LEFT", true);
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	m_ePrevState = m_eCurState;

	update_move();

	update_state();

	update_animation();

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	// 컴포넌트(충돌체, etc...)가 있는 경우 렌더.
	component_render(_dc);
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

void CPlayer::update_state()
{
	if (KEY_HOLD(KEY::LEFT))
	{
		m_iDir = -1;
		m_eCurState = PLAYER_STATE::WALK;
	}

	if (KEY_HOLD(KEY::RIGHT))
	{
		m_iDir = 1;
		m_eCurState = PLAYER_STATE::WALK;
	}
}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::UP))
	{
		pRigid->AddForce(Vec2(0.f, -200.f));
	}

	if (KEY_HOLD(KEY::DOWN))
	{
		pRigid->AddForce(Vec2(0.f, 200.f));
	}

	if (KEY_HOLD(KEY::LEFT))
	{
		pRigid->AddForce(Vec2(-200.f, 0.f));
	}

	if (KEY_HOLD(KEY::RIGHT))
	{
		pRigid->AddForce(Vec2(200.f, 0.f));
	}



	if (KEY_TAP(KEY::UP))
	{
		pRigid->AddVelocity(Vec2(0.f, -100.f));
	}

	if (KEY_TAP(KEY::DOWN))
	{
		pRigid->AddVelocity(Vec2(0.f, 100.f));
	}

	if (KEY_TAP(KEY::LEFT))
	{
		pRigid->AddVelocity(Vec2(-100.f, 0.f));
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		pRigid->AddVelocity(Vec2(100.f, 0.f));
	}
}

void CPlayer::update_animation()
{
	if (m_ePrevState == m_eCurState)
		return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:

		break;
	case PLAYER_STATE::WALK:

		break;
	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DEAD:

		break;
	}
}
