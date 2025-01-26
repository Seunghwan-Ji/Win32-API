#include "pch.h"
#include "CScene.h"
#include "CObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	// 오브젝트 삭제.
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) // 벡터 배열 순회.
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) // 오브젝트 배열 순회.
		{
			// m_arrObj[i] 그룹 벡터의 j 물체 삭제.
			delete m_arrObj[i][j];
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// 삭제 예정이 아닌 오브젝트만 업데이트.
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->update();
			}
		}
	}
}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// 삭제 예정인 오브젝트여도, 충돌 검사를 마무리하기 위해 조건 없이 모두 finalupdate.
			m_arrObj[i][j]->finalupdate(); // 오브젝트의 충돌 영역 위치 조정.
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			// 삭제 예정이 아닌 오브젝트만 렌더링.
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}
