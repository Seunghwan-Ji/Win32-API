#include "pch.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::update()
{
	// 행 순회.
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		// 열 순회.
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
			// 중복 검사 방지를 위해 열 시작 번호는 행 번호와 동일.
		{
			if (m_arrCheck[iRow] & (1 << iCol)) // iCol번째 비트가 1인지 확인.
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	// 지역변수에 GetGroupObject 함수가 반환한 원본을 받았다고 해서 지역변수에 원본이 저장되는 것이
	// 아니므로, 지역변수도 상수화한 레퍼런스 형태로 받는다.

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 왼쪽 그룹에 속해있는 오브젝트가 충돌 기능이 있는지 확인.
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// 오른쪽 그룹에 속해있는 오브젝트가 충돌 기능이 있는지 확인.
			// + 자기 자신 오브젝트와의 충돌 방지 조건.
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
			{
				continue;
			}

			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{

			}
			else
			{

			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{


	return false;
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트) 로 사용.

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) // iCol번째 비트가 1인지 확인.
	{
		m_arrCheck[iRow] &= ~(1 << iCol); // iCol번째 비트를 0으로 설정.
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol); // iCol번째 비트를 1로 설정.
	}
}
