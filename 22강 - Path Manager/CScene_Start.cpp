#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CPathMgr.h"
#include "CTexture.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// Texture 로딩하기.
	CTexture* pTex = new CTexture;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"texture\\Player.bmp";
	pTex->Load(strFilePath); // 여기에 중단점 걸고 디버그 모드 이미지 로드 성공 여부 확인.

	delete pTex;

	// Object 추가.
	CObject* pObj = new CPlayer;

	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::DEFAULT); // 오브젝트의 주소와 타입 전달.

	// 몬스터 배치.
	int iMonCount = 16; // 몬스터 수.
	float fMoveDist = 25.f; // 이동 반경.
	float fObjScale = 50.f; // 몬스터 크기.

	Vec2 vResolution = CCore::GetInst()->GetResolution(); // 윈도우 해상도.
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1); // 몬스터 배치 간격.

	CMonster* pMonsterObj = nullptr;

	for (int i = 0; i < iMonCount; ++i)
	{
		// Monster Object 추가.
		pMonsterObj = new CMonster;
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::DEFAULT);
	}
}

void CScene_Start::Exit()
{
}
