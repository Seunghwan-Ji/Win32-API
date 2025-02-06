#include "pch.h"
#include "CTile.h"
#include "CTexture.h"

CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iIdx(47)
{
	// 타일 오브젝트의 스케일을 선언된 타일 사이즈 만큼 설정.
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::update()
{
}

void CTile::render(HDC _dc)
{
	if (nullptr == m_pTileTex || -1 == m_iIdx)
		return;

	// 모든 타일 집합 텍스쳐의 전체 너비 및 높이.
	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	// 너비에 대한 최대 열, 높이에 대한 최대 행 계산.
	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	// 선택한 타일의 순번 m_iIdx 이 해당하는 행, 열 계산.
	UINT iCurRow = (UINT)m_iIdx / iMaxCol; // ex) 순번 47 을 '최대 열'로 나눈 몫.
	UINT iCurCol = (UINT)m_iIdx % iMaxCol; // ex) 순번 47 을 '최대 열'로 나눈 나머지.

	// 이미지 범위를 벗어난 순번의 경우 예외처리.
	if (iMaxRow <= iCurRow)
		assert(nullptr);
	// iCurCol 은 최대 값 iMaxCol 범위 안에서만 나오므로 생략 가능.

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos()); // 타일 오브젝트를 렌더링 할 좌표 계산.
	Vec2 vScale = GetScale();

	BitBlt(_dc				  // 메인 윈도우의 DC.
		, int(vRenderPos.x)   // 그릴 좌상단 x 좌표.
		, int(vRenderPos.y)	  // 그릴 좌상단 y 좌표.
		, int(vScale.x)		  // 그릴 너비.
		, int(vScale.y)		  // 그릴 높이.
		, m_pTileTex->GetDC() // 텍스쳐의 DC.
		, iCurCol * TILE_SIZE // 텍스쳐 내에서 자를 영역의 좌상단 x 좌표.
		, iCurRow * TILE_SIZE // 텍스쳐 내에서 자를 영역의 좌상단 y 좌표.
		, SRCCOPY);			  // 복사 방식: 자른 영역 그대로 복사.

	/*Rectangle(_dc
		, int(vRenderPos.x)
		, int(vRenderPos.y)
		, int(vRenderPos.x + vScale.x)
		, int(vRenderPos.y + vScale.y));*/
}