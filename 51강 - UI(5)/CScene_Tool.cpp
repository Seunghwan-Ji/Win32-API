#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"
#include "resource.h"
#include "CSceneMgr.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
	// Ÿ�� ����.
	CreateTile(5, 5);

	// UI �ϳ� ������.
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// ������ â ���ܿ� ��ġ.

	// �θ� UI ������Ʈ ����.
	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(500.f, 300.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

	// �ڽ� UI ������Ʈ ����.
	CUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	
	pPanelUI->AddChild(pBtnUI); // �θ� UI �� �ڽ� UI �߰�.

	AddObject(pPanelUI, GROUP_TYPE::UI); // �θ� UI �� �߰� �����ν� �ڽ� UI �� ���� �߰���.

	// UI ����.
	CUI* pClonePanel = pPanelUI->Clone();
	pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
	AddObject(pClonePanel, GROUP_TYPE::UI);

	// Camera Look ����.
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{

}

void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();
}

void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		// Ŭ���� ���콺 ��ǥ.
		Vec2 vMousePos = MOUSE_POS;

		// ���� ��ǥ�� ��ȯ.
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		// ����, ���� Ÿ�� ����.
		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		// ���콺�� ��ǥ�� Ÿ�� �ϳ��� ������� ������ ��, �� ��ȣ�� �˾Ƴ�.
		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		// Ÿ���� �ƴ� ���� Ŭ�� ���� ��� ���� ó��.
		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		// Ÿ�� �׷��� 1���� ���� �̹Ƿ�, 2���� ��� �ε����� 1���� �ε����� ���.
		UINT iIdx = iRow * iTileX + iCol;
		// 1. �� ���� ������ ��ü Ÿ�� ���� ����.
		// 2. ���� Ÿ�� ���� �� ��ȣ�� ����.

		// Ÿ�� �׷쿡 �ε���.
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx(); // Ÿ�� ������Ʈ�� �̹��� �ε��� ����.
	}
}





// ======================
// Tile Count Window Proc
// ======================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// GetDlgItemInt: �Է��� ���� �ؽ�Ʈ�� ���� ������ �������� �Լ�.
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			// ���� �� Ȯ��.
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// ToolScene ���� Ȯ��.(�ٿ�ĳ���� �õ�)
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			// ���� Ÿ�� ������Ʈ ����.
			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			
			// �� Ÿ�� ������Ʈ ����.
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			// EndDialog �Լ��� ��ȯ ���� �����ϸ�, ���� ������ ���� ���,
			// �ι�° ������ ���� �޴´�.
			// ���� IDOK �Ǵ� IDCANCEL �̴�.
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}