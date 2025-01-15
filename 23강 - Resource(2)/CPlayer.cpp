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
	// Texture �ε��ϱ�.
	m_pTex = new CTexture;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"texture\\Player.bmp";
	m_pTex->Load(strFilePath); // ���⿡ �ߴ��� �ɰ� ����� ��� �̹��� �ε� ���� ���� Ȯ��.
}

CPlayer::~CPlayer()
{
	if (nullptr != m_pTex)
		delete m_pTex;
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
		, m_pTex->GetDC()    // �ҽ� �̹����� ��Ʈ���� �����ϰ� �ִ� DC.
		, 0, 0			     // �ҽ� �̹������� ������ �κ��� ���� ��ǥ.
		, iWidth, iHeight    // ���� ��ǥ�κ��� ������ �ʺ�� ����.
		, RGB(255, 0, 255)); // �ҽ� �̹������� �������� ���� �ȼ� ����.(���� ó���� ����)
	// TransparentBlt �Լ��� ���� �뵵�� ���̱� ������ ���ڿ� SRCCOPY �� �����Ѵ�.
	// (255, 0, 255) ���� �̷� ��ũ ������ ����Ÿ �����̶�� �Ҹ���, �Ϲ������� �� ������ �ʴ� ����
	// �̱� ������ ���� ó�� �뵵�� ���δ�.
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
