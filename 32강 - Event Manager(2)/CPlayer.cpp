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
	// Texture 로딩하기.
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	CreateCollider(); // 충돌 영역 생성.
	GetCollider()->SetOffsetPos(Vec2(0.f, 12.f)); // 충돌 영역 위치 조정.
	GetCollider()->SetScale(Vec2(20.f, 40.f)); // 충돌 영역 사이즈 조정.
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	Vec2 vPos = GetPos(); // 부모 클래스를 통해 좌표 받아오기.

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

	SetPos(vPos); // 부모 클래스를 통해 좌표 갱신.
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
		, m_pTex->GetDC()    // 소스 이미지의 비트맵을 선택하고 있는 DC.
		, 0, 0			     // 소스 이미지에서 복사할 부분의 시작 좌표.
		, iWidth, iHeight    // 시작 좌표로부터 복사할 너비와 높이.
		, RGB(255, 0, 255)); // 소스 이미지에서 복사하지 않을 픽셀 색상.(투명 처리할 색상)

	// 컴포넌트(충돌체, etc...)가 있는 경우 렌더.
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
