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
	// Texture 로딩하기.
	// m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	CreateCollider(); // 충돌 영역 생성.
	GetCollider()->SetOffsetPos(Vec2(0.f, 12.f)); // 충돌 영역 위치 조정.
	GetCollider()->SetScale(Vec2(20.f, 40.f)); // 충돌 영역 사이즈 조정.

	// Texture 로딩하기.
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link_0.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f)
		, Vec2(60.f, 0.f), 0.08f, 10);
	GetAnimator()->Play(L"WALK_DOWN", true);

	// 텍스쳐를 오브젝트 위치보다 위쪽에 배치.
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

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos); // 부모 클래스를 통해 좌표 갱신.

	GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	// 컴포넌트(충돌체, etc...)가 있는 경우 렌더.
	// component_render(_dc);

	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Plane", L"texture\\Player_A.bmp");

	Vec2 vPos = GetPos(); // 좌표 받아오기.
	vPos = CCamera::GetInst()->GetRenderPos(vPos); // 렌더링 좌표로 변환.

	// 텍스처 스케일 정보.
	float width = (float)pTex->Width();
	float height = (float)pTex->Height();

	// AlphaBlend 함수의 마지막 인자에 넣는 옵션인 객체.
	// 다음 구문들은 Microsoft Learn 문서에 나온 양식임.
	BLENDFUNCTION bf = {};

	// 기존 배경 위에 새 이미지를 알파 블렌딩 방식으로 덮어 씌운다.
	bf.BlendOp = AC_SRC_OVER;

	// 사용되지 않는 필드이므로 항상 0으로 설정.
	bf.BlendFlags = 0;
	
	// 소스 이미지 자체에 포함된 알파 채널(투명도 정보)을 사용.
	// 즉, 픽셀별로 개별적인 투명도를 적용할 수 있음.
	bf.AlphaFormat = AC_SRC_ALPHA;

	// 소스 이미지의 전체 투명도를 255(완전 불투명)로 설정.
	// 즉, 소스 이미지의 자체 알파 채널 값만 적용됨.
	bf.SourceConstantAlpha = 255;

	AlphaBlend(_dc
		// 렌더링 목적지 시작 좌표 및 스케일.
		, int(vPos.x - width / 2.f)
		, int(vPos.y - height / 2.f)
		, int(width), int(height)
		// 텍스처 DC.
		, pTex->GetDC()
		// 텍스처에서 복사를 시작할 좌표 및 스케일.
		, 0, 0
		, int(width), int(height)
		// 위 양식대로 작성된 객체를 넣는 이 함수의 마지막 옵션.
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
