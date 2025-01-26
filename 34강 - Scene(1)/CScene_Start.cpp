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

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update(); // 어차피 부모쪽 업데이트 함수를 호출할건데 굳이 자식쪽에서
					  // 업데이트 함수를 오버라이딩해서 여기로 들어온 이유는,
					  // 아래에서 씬 전환 작업을 하기 위함이다.

	if (KEY_TAP(KEY::S))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
}

void CScene_Start::Enter()
{
	// 플레이어 오브젝트 추가.
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER); // 오브젝트의 주소와 타입 전달.

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

	// 충돌 지정.
	// 그룹 간의 충돌 체크.
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}
