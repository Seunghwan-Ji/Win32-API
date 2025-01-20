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
	// �� ��ȸ.
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		// �� ��ȸ.
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
			// �ߺ� �˻� ������ ���� �� ���� ��ȣ�� �� ��ȣ�� ����.
		{
			if (m_arrCheck[iRow] & (1 << iCol)) // iCol��° ��Ʈ�� 1���� Ȯ��.
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
	// ���������� GetGroupObject �Լ��� ��ȯ�� ������ �޾Ҵٰ� �ؼ� ���������� ������ ����Ǵ� ����
	// �ƴϹǷ�, ���������� ���ȭ�� ���۷��� ���·� �޴´�.

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// ���� �׷쿡 �����ִ� ������Ʈ�� �浹 ����� �ִ��� Ȯ��.
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// ������ �׷쿡 �����ִ� ������Ʈ�� �浹 ����� �ִ��� Ȯ��.
			// + �ڱ� �ڽ� ������Ʈ���� �浹 ���� ����.
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
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ) �� ���.

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) // iCol��° ��Ʈ�� 1���� Ȯ��.
	{
		m_arrCheck[iRow] &= ~(1 << iCol); // iCol��° ��Ʈ�� 0���� ����.
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol); // iCol��° ��Ʈ�� 1�� ����.
	}
}
