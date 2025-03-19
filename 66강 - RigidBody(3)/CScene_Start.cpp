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
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"

CScene_Start::CScene_Start()
	: m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	if (KEY_HOLD(KEY::LBTN))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
	}

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);

		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			// 삭제 예정이 아닌 오브젝트만 업데이트.
			if (!vecObj[j]->IsDead())
			{
				// 힘을 사용하고, 강체가 있으면 힘을 가함.
				if (m_bUseForce && vecObj[j]->GetRigidBody())
				{
					// 힘을 가할 위치와 오브젝트의 위치 차이.
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					
					// 차이의 길이.
					float fLen = vDiff.Length();

					// 힘의 반경 내에 있으면 힘을 가함.
					if (fLen < m_fForceRadius)
					{
						// 힘의 세기는 거리에 반비례.
						float fRatio = 1.f - (fLen / m_fForceRadius); // 0 ~ 1.

						// 힘의 세기.
						float fForce = m_fForce * fRatio; // 거리가 가까울수록 세기가 강해짐.

						// 힘을 가함.
						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);
					}
				}

				vecObj[j]->update();
			}
		}
	}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	//if (KEY_TAP(KEY::LBTN))
	//{
	//	// 마우스의 좌표는 렌더링 상의 좌표이므로, 클릭한 곳을 맵상에서의 실제 좌표로 얻어옴.
	//	Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
	//	CCamera::GetInst()->SetLookAt(vLookAt);
	//}
}

void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);

	if (!m_bUseForce)
		return; // 힘을 사용하지 않으면 렌더링하지 않음.

	SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	m_fCurRadius += m_fForceRadius * 3.f * fDT;
	if (m_fCurRadius > m_fForceRadius)
	{
		m_fCurRadius = 0.f;
	}

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);

	// 힘을 가할 위치를 표시.
	Ellipse(_dc
		, vRenderPos.x - m_fCurRadius // 왼쪽 위.
		, vRenderPos.y - m_fCurRadius
		, vRenderPos.x + m_fCurRadius // 오른쪽 아래.
		, vRenderPos.y + m_fCurRadius);
}

void CScene_Start::Enter()
{
	// 플레이어 오브젝트 추가.
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER); // 오브젝트의 주소와 타입 전달.

	RegisterPlayer(pObj); // 플레이어 등록.

	// 플레이어 오브젝트 복사.
	// CObject* pOtherPlayer = pObj->Clone();
	// pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	// AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	// 플레이어를 카메라가 추적.
	// CCamera::GetInst()->SetTarget(pObj);

	// 몬스터 배치.
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	// 타일 로딩
	// LoadTile(L"Tile\\Start.tile");

	// 충돌 지정.
	// 그룹 간의 충돌 체크.
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	// Camera Look 지정.
	CCamera::GetInst()->SetLookAt(vResolution / 2.f); // 해상도 중앙 좌표.

	// Camera 효과 지정.
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
}
