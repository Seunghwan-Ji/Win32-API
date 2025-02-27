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
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC mainDC = CCore::GetInst()->GetMainDC();

	// 이중 버퍼링 용도의 비트맵과 DC 를 만든다.(이중 렌더링)
	// 윈도우 해상도 크기만큼 비트맵 생성.
	m_hBit = CreateCompatibleBitmap(mainDC, _iWidth, _iHeight);

	// 생성한 비트맵에 그리기 작업을 할 DC 생성.
	m_dc = CreateCompatibleDC(mainDC);

	// DC 가 그릴 목적지를, 생성한 비트맵으로 지정해준다.
	HBITMAP hOldBIt = (HBITMAP)SelectObject(m_dc, m_hBit);

	// DC 가 갖고 있던 기본 비트맵 제거.
	DeleteObject(hOldBIt);

	// 비트맵 정보.
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
