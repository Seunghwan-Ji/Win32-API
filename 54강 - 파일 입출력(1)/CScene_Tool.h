#pragma once

#include "CScene.h"

class CScene_Tool :
    public CScene
{
private:
    CUI* m_pUI; // ����Ű�� ������ ��, ��� UI.

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    void SetTileIdx(); // ���콺�� Ŭ���� Ÿ���� �ε����� �������� Ÿ���� �����Ű�� �Լ�.

    void SaveTile(const wstring& _strRekativePath);

public:
    CScene_Tool();
    ~CScene_Tool();
};

