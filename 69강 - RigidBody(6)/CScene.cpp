#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CCore.h"

CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
	, m_pPlayer(nullptr)
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

void CScene::start()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->start();
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
		if ((UINT)GROUP_TYPE::TILE == i)
		{
			render_tile(_dc);
			continue;
		}

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

void CScene::render_tile(HDC _dc)
{
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	// 카메라가 보는 곳의 중심 좌표.
	Vec2 vCamLook = CCamera::GetInst()->GetLookAt();

	// 카메라 해상도.
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// 카메라의 좌상단 좌표.
	Vec2 vLeftTop = vCamLook - vResolution / 2.f;

	int iTileSize = TILE_SIZE;

	// 좌상단 좌표의 행렬 구하기.
	int iLTCol = (int)vLeftTop.x / iTileSize;
	int iLTRow = (int)vLeftTop.y / iTileSize;

	// 구한 행렬이 평탄화(1차원)한 타일에서 몇 번째인지 계산하기.
	// int iLTIdx = (m_iTileX * iLTRow) + iLTCol;

	// 해상도에 채워지는 타일 단위의 너비와 높이 구하기.
	int iClientWidth = ((int)vResolution.x / iTileSize) + 1;
	int iClientHeight = ((int)vResolution.y / iTileSize) + 1;
	// 해상도 테두리에 타일이 살짝 걸칠 경우, 정수 나눗셈 특성 때문에
	// 걸쳐진 부분은 타일이 렌더링 되지 않게된다.
	// 그러므로 타일 단위 해상도 너비와 높이에 + 1.

	for (int iCurRow = iLTRow; iCurRow < (iLTRow + iClientHeight); ++iCurRow)
	{
		for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); ++iCurCol)
		{
			// 맵 바깥 예외 처리.
			if (iCurCol < 0 || (int)m_iTileX <= iCurCol
				|| iCurRow < 0 || (int)m_iTileY <= iCurRow)
			{
				continue;
			}

			// 1차원 인덱스.
			int iIdx = (m_iTileX * iCurRow) + iCurCol;

			// 1차원 타일 벡터에 인덱스로 접근 후 렌더링 진행.
			// 벡터가 비었을 경우 예외처리.
			if (iIdx >= 0 && iIdx < vecTile.size()) {
				vecTile[iIdx]->render(_dc);
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
	// 기존 타일 삭제.
	DeleteGroup(GROUP_TYPE::TILE);

	// 가로, 세로 타일 개수 갱신.
	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	// 텍스쳐 로드.
	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\TILE.bmp");

	// 타일 생성.
	for (UINT i = 0; i < _iYCount; ++i) // 행
	{
		for (UINT j = 0; j < _iXCount; ++j) // 열
		{
			CTile* pTile = new CTile;

			// 각 타일의 좌표는 행, 열 인덱스에 타일 사이즈를 곱한 값으로 설정.
			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::LoadTile(const wstring& _strRelativePath)
{
	// content 폴더 까지의 절대 경로 불러오기
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	// 상대 경로 이어 붙이기.
	strFilePath += _strRelativePath;

	// 커널 오브젝트.
	FILE* pFile = nullptr;

	// 바이너리 모드로 읽기.
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	assert(pFile);

	// 데이터 불러오기.

	// 타일 가로 및 세로 개수 불러오기.
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	// 불러온 개수에 맞게 EmptyTile 들 만들어두기.
	CreateTile(xCount, yCount);

	// 만들어진 타일 개별로 필요한 정보를 불러오게 함.
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	// 파일 닫기.
	fclose(pFile);
}
