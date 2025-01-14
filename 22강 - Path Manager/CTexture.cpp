#include "pch.h"
#include "CTexture.h"

CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP
		, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	// 1. nullptr
	// 리소스 핸들. 여기서는 nullptr로 설정하여 애플리케이션 리소스가 아닌 외부 파일에서 이미지를
	// 로드하겠다는 것을 나타냅니다.

	// 2. _strFilePath.c_str()
	// _strFilePath는 wstring 타입으로 전달되며, .c_str()를 통해 const wchar_t*로 변환하여 파일
	// 경로를 API에 전달합니다.

	// 3. IMAGE_BITMAP
	// 불러올 리소스 유형을 지정합니다. 여기서는 비트맵 이미지를 의미합니다.

	// 4. 0, 0
	// 이미지를 로드할 때 사용할 너비와 높이를 지정합니다. 0으로 설정하면 기본 크기로 로드합니다.

	// 5. LR_CREATEDIBSECTION | LR_LOADFROMFILE
	// 로드 옵션을 설정하는 플래그입니다:
	// - LR_CREATEDIBSECTION
	//	 비트맵 데이터에 직접 접근할 수 있는 메모리 매핑 개체를 생성합니다.
	// - LR_LOADFROMFILE
	//   지정된 파일 경로에서 이미지를 로드합니다.

	// 함수 반환 타입
	// LoadImage는 반환값으로 HANDLE을 제공합니다.
	// HANDLE은 Windows API에서 다양한 리소스(파일, 비트맵, 아이콘 등)의 핸들을 저장하는 일반적인
	// 타입입니다.
	// 반환된 HANDLE은 호출한 리소스의 유형에 따라 적절한 특화된 핸들 타입으로 변환하여 사용해야
	// 합니다.
	// (HBITMAP) 형 변환은 컴파일러에게 "이 핸들을 비트맵으로 사용할 것"임을 알리는 명확한 신호를
	// 줍니다.

	assert(m_hBit); // 이미지 로드가 실패하면 예외처리.
}