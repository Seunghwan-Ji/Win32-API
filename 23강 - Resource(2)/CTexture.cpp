#include "pch.h"
#include "CTexture.h"
#include "CCore.h"
#include "CRes.h"

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
	// 파일로 부터 로딩한 데이터를 비트맵으로 생성.
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP
		, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit); // 이미지 로드가 실패하면 예외처리.

	// 비트맵과 연결할 DC.
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// 비트맵과 DC 연결.
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// 비트맵 정보.
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo); // 구조체에 비트맵의 정보를 기록해주는 함수.
	// 매개변수: 비트맵 객체, 구조체의 크기, 구조체의 주소
}