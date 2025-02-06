#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"
#include "CResMgr.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	// ������Ʈ ����.
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) // ���� �迭 ��ȸ.
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) // ������Ʈ �迭 ��ȸ.
		{
			// m_arrObj[i] �׷� ������ j ��ü ����.
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
			// ���� ������ �ƴ� ������Ʈ�� ������Ʈ.
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
			// ���� ������ ������Ʈ����, �浹 �˻縦 �������ϱ� ���� ���� ���� ��� finalupdate.
			m_arrObj[i][j]->finalupdate(); // ������Ʈ�� �浹 ���� ��ġ ����.
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
			// ���� ������ �ƴ� ������Ʈ�� ������.
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
	Safe_Delete_Vec<CObject*> (m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	// ����, ���� Ÿ�� ���� ����.
	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	// �ؽ��� �ε�.
	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\TILE.bmp");

	// Ÿ�� ����.
	for (UINT i = 0; i < _iYCount; ++i) // ��
	{
		for (UINT j = 0; j < _iXCount; ++j) // ��
		{
			CTile* pTile = new CTile;

			// �� Ÿ���� ��ǥ�� ��, �� �ε����� Ÿ�� ����� ���� ������ ����.
			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}
