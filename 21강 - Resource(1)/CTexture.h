#pragma once

#include "CRes.h"

// �ؽ��Ĵ� ������Ʈ�� ���� �̹��� �����͸� ����.

class CTexture :
    public CRes
{
private:
    HDC     m_dc; // ���ҽ� �̹����� �׸� DC.(m_hBit �� �׸� �뵵)
    HBITMAP m_hBit; // ���ҽ� �̹��� �ػ� ũ�� ��ŭ�� ��Ʈ��.

public:
    CTexture();
    ~CTexture();
};