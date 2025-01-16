#pragma once

#include "CRes.h"

// �ؽ��Ĵ� ������Ʈ�� ���� �̹��� �����͸� ����.

class CTexture :
    public CRes
{
private:
    HDC     m_dc;      // ���ҽ� �̹����� �׸� DC.(m_hBit �� �׸� �뵵)
    HBITMAP m_hBit;    // ���ҽ� �̹��� �ػ� ũ�� ��ŭ�� ��Ʈ��.
    BITMAP  m_bitInfo; // ��Ʈ�� ��ü�� ������ ������ �� �ִ� ����ü.

public:
    void Load(const wstring& _strFilePath);

    UINT Width() { return m_bitInfo.bmWidth; } // ��Ʈ�� ��ü�� ���� ������.
    UINT Height() { return m_bitInfo.bmHeight; } // ��Ʈ�� ��ü�� ���� ������.

    HDC GetDC() { return m_dc; }

private:
    CTexture();
    ~CTexture();

    friend class CResMgr; // �����ڿ� �Ҹ��ڸ� ���ҽ� �Ŵ��� Ŭ���������� ȣ�� �����ϰ� ����.
};