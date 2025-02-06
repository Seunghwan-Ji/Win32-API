#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"
#include "resource.h"
#include "CSceneMgr.h"

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

	// Camera Look ����.
	Vec2 vResolution = CCore::GetInst()->GetResolution();
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
		UINT iTileX = GetTileX();
		UINT iTileY = GetTileY();

		// ���콺�� ��ǥ�� Ÿ�� �ϳ��� ������� ������ ��, �� ��ȣ�� �˾Ƴ�.
		UINT iCol = (UINT)vMousePos.x / TILE_SIZE;
		UINT iRow = (UINT)vMousePos.y / TILE_SIZE;

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
			// ���ҽ� �信�� Ÿ�� ���� �Է¶��� ��Ŭ�� ��, �Ӽ����� '����' �κ��� True �� �����ϸ�,
			// Ÿ�� ���� �Է¶��� ���ڸ� �Է��� �� �ִ�.

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