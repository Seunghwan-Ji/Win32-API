#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		// 마우스의 좌표는 렌더링 상의 좌표이므로, 클릭한 곳을 맵상에서의 실제 좌표로 얻어옴.
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
}

void CScene_Start::Enter()
{
	// 플레이어 오브젝트 추가.
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER); // 오브젝트의 주소와 타입 전달.

	// 플레이어 오브젝트 복사.
	// CObject* pOtherPlayer = pObj->Clone();
	// pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	// AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	// 플레이어를 카메라가 추적.
	// CCamera::GetInst()->SetTarget(pObj);

	// 몬스터 배치.
	int iMonCount = 7; // 몬스터 수.
	float fMoveDist = 25.f; // 이동 반경.
	float fObjScale = 50.f; // 몬스터 크기.

	// 윈도우 해상도.
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// 몬스터 배치 간격.
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);

	// 몬스터 오브젝트 추가.
	CMonster* pMonsterObj = nullptr;
	for (int i = 0; i < iMonCount; ++i)
	{
		pMonsterObj = new CMonster;
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// 타일 로딩
	// LoadTile(L"Tile\\Start.tile");

	// 충돌 지정.
	// 그룹 간의 충돌 체크.
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	// Camera Look 지정.
	CCamera::GetInst()->SetLookAt(vResolution / 2.f); // 해상도 중앙 좌표.
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}
