#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CPathMgr.h"
#include "CTexture.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	// Texture 로딩하기.
	m_pTex = new CTexture;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"texture\\Player.bmp";
	m_pTex->Load(strFilePath); // 여기에 중단점 걸고 디버그 모드 이미지 로드 성공 여부 확인.
}

CPlayer::~CPlayer()
{
	if (nullptr != m_pTex)
		delete m_pTex;
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

	/*BitBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, SRCCOPY);*/

	TransparentBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()    // 소스 이미지의 비트맵을 선택하고 있는 DC.
		, 0, 0			     // 소스 이미지에서 복사할 부분의 시작 좌표.
		, iWidth, iHeight    // 시작 좌표로부터 복사할 너비와 높이.
		, RGB(255, 0, 255)); // 소스 이미지에서 복사하지 않을 픽셀 색상.(투명 처리할 색상)
	// TransparentBlt 함수는 복사 용도로 쓰이기 때문에 인자에 SRCCOPY 는 생략한다.
	// (255, 0, 255) 보통 이런 핑크 색상을 마젠타 색상이라고 불리며, 일반적으로 잘 쓰이지 않는 색상
	// 이기 때문에 투명 처리 용도로 쓰인다.
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

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}
