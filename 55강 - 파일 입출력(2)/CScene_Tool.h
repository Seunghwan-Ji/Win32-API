#pragma once

#include "CScene.h"

class CScene_Tool :
    public CScene
{
private:
    CUI* m_pUI; // 단축키를 눌렀을 때, 띄울 UI.

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    void SetTileIdx(); // 마우스로 클릭한 타일의 인덱스를 증가시켜 타일을 변경시키는 함수.

    void SaveTileData(); // 파일 저장 경로와 이름을 설정하기 위한 Dialog UI 실행 함수.
    void SaveTile(const wstring& _strFilePath); // 경로를 받아 실제로 데이터를 저장하는 함수.

    void LoadtileData();

public:
    CScene_Tool();
    ~CScene_Tool();
};

