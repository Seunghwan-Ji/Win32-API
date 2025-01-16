#pragma once

#include "CRes.h"

// 텍스쳐는 오브젝트에 입힐 이미지 데이터를 말함.

class CTexture :
    public CRes
{
private:
    HDC     m_dc;      // 리소스 이미지를 그릴 DC.(m_hBit 에 그릴 용도)
    HBITMAP m_hBit;    // 리소스 이미지 해상도 크기 만큼의 비트맵.
    BITMAP  m_bitInfo; // 비트맵 객체의 정보를 저장할 수 있는 구조체.

public:
    void Load(const wstring& _strFilePath);

    UINT Width() { return m_bitInfo.bmWidth; } // 비트맵 객체의 가로 사이즈.
    UINT Height() { return m_bitInfo.bmHeight; } // 비트맵 객체의 높이 사이즈.

    HDC GetDC() { return m_dc; }

private:
    CTexture();
    ~CTexture();

    friend class CResMgr; // 생성자와 소멸자를 리소스 매니저 클래스에서만 호출 가능하게 설정.
};