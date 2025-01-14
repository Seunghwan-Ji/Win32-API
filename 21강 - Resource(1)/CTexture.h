#pragma once

#include "CRes.h"

// 텍스쳐는 오브젝트에 입힐 이미지 데이터를 말함.

class CTexture :
    public CRes
{
private:
    HDC     m_dc; // 리소스 이미지를 그릴 DC.(m_hBit 에 그릴 용도)
    HBITMAP m_hBit; // 리소스 이미지 해상도 크기 만큼의 비트맵.

public:
    CTexture();
    ~CTexture();
};