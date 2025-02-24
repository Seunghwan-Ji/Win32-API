#include "pch.h"
#include "CTile.h"
#include "CTexture.h"

CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImgIdx(0)
{
	// Ÿ�� ������Ʈ�� �������� ����� Ÿ�� ������ ��ŭ ����.
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
	if (nullptr == m_pTileTex || -1 == m_iImgIdx)
		return;

	// ��� Ÿ�� ���� �ؽ����� ��ü �ʺ� �� ����.
	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	// �ʺ� ���� �ִ� ��, ���̿� ���� �ִ� �� ���.
	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	// ������ Ÿ���� ���� m_iImgIdx �� �ش��ϴ� ��, �� ���.
	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol; // ex) ���� 47 �� '�ִ� ��'�� ���� ��.
	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol; // ex) ���� 47 �� '�ִ� ��'�� ���� ������.

	// �̹��� ������ ��� ������ ��� ����ó��.
	if (iMaxRow <= iCurRow)
		assert(nullptr);
	// iCurCol �� �ִ� �� iMaxCol ���� �ȿ����� �����Ƿ� ���� ����.

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos()); // Ÿ�� ������Ʈ�� ������ �� ��ǥ ���.
	Vec2 vScale = GetScale();

	BitBlt(_dc				  // ���� �������� DC.
		, int(vRenderPos.x)   // �׸� �»�� x ��ǥ.
		, int(vRenderPos.y)	  // �׸� �»�� y ��ǥ.
		, int(vScale.x)		  // �׸� �ʺ�.
		, int(vScale.y)		  // �׸� ����.
		, m_pTileTex->GetDC() // �ؽ����� DC.
		, iCurCol * TILE_SIZE // �ؽ��� ������ �ڸ� ������ �»�� x ��ǥ.
		, iCurRow * TILE_SIZE // �ؽ��� ������ �ڸ� ������ �»�� y ��ǥ.
		, SRCCOPY);			  // ���� ���: �ڸ� ���� �״�� ����.
}

void CTile::Save(FILE* _pFile)
{
	// Ÿ�� �ؽ�ó �ε��� ���� ����.
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	// Ÿ�� �ؽ�ó �ε��� ���� �ҷ�����.
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}
