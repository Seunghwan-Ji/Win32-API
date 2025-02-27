#include "pch.h"
#include "CTexture.h"
#include "CRes.h"
#include "CCore.h"

CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// ���Ϸ� ���� �ε��� �����͸� ��Ʈ������ ����.
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP
		, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit); // �̹��� �ε尡 �����ϸ� ����ó��.

	// ��Ʈ�ʰ� ������ DC.
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// ��Ʈ�ʰ� DC ����.
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// ��Ʈ�� ����.
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo); // ����ü�� ��Ʈ���� ������ ������ִ� �Լ�.
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC mainDC = CCore::GetInst()->GetMainDC();

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC �� �����.(���� ������)
	// ������ �ػ� ũ�⸸ŭ ��Ʈ�� ����.
	m_hBit = CreateCompatibleBitmap(mainDC, _iWidth, _iHeight);

	// ������ ��Ʈ�ʿ� �׸��� �۾��� �� DC ����.
	m_dc = CreateCompatibleDC(mainDC);

	// DC �� �׸� ��������, ������ ��Ʈ������ �������ش�.
	HBITMAP hOldBIt = (HBITMAP)SelectObject(m_dc, m_hBit);

	// DC �� ���� �ִ� �⺻ ��Ʈ�� ����.
	DeleteObject(hOldBIt);

	// ��Ʈ�� ����.
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
