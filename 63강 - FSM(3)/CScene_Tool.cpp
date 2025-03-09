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
#include "CUIMgr.h"
#include "CPathMgr.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
	// �� Scene ���� ����� �޴��� ���δ�.
	CCore::GetInst()->DockMenu();

	// Ÿ�� ����.
	CreateTile(5, 5);

	// UI �ϳ� ������.
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// ������ â ���ܿ� ��ġ.

	// �θ� UI ������Ʈ ����.
	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 150.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

	// �ڽ� UI ������Ʈ ����.
	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(30.f, 20.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));

	// �� UI �� ���� �ݹ� �Լ� ����.
	((CBtnUI*)pBtnUI)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SaveTileData);
	// (SCENE_MEMFUNC): �Լ� �����Ϳ��� ������ ��� �Լ� Ÿ������ ������� ĳ������ ������Ѵ�.
	
	pPanelUI->AddChild(pBtnUI); // �θ� UI �� �ڽ� UI �߰�.

	AddObject(pPanelUI, GROUP_TYPE::UI); // �θ� UI �� �߰� �����ν� �ڽ� UI �� ���� �߰���.

	// UI ����.
	// CUI* pClonePanel = pPanelUI->Clone();
	// pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
	
	// ���纻 UI �� �ڽ� UI �ʿ� �ݹ� �Լ� ����.
	// ((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClikedCallBack(ChangeScene, 0, 0);
	
	// AddObject(pClonePanel, GROUP_TYPE::UI);

	// ����Ű�� ��Ŀ�� �� UI.
	// m_pUI = pClonePanel;

	// Camera Look ����.
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
	CCore::GetInst()->DivideMenu();

	DeleteAll();
}

void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();

	// ���� ����Ʈ Ű�� ������ ���� ����.
	// if (KEY_TAP(KEY::LSHIFT))
	// {
	// 	// CUIMgr::GetInst()->SetFocusedUI(m_pUI);
	// 	SaveTileData();
	// }

	// ��Ʈ�� Ű�� ������ ���� �ҷ��ͼ� �б�.
	if (KEY_TAP(KEY::CTRL))
	{
		LoadtileData();
	}
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

void CScene_Tool::SaveTileData()
{
	wchar_t szName[256] = {}; // �������� ���� ��� �迭.(���� ���)

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME); // ����ü ������ ����.
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd(); // �θ� ������ ����.
	ofn.lpstrFile = szName; // ���� ��� �迭�� ���� �ּ�.
	ofn.nMaxFile = sizeof(szName); // �迭�� ������.
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0"; // ���Ϳ� ���� Ȯ���� ����.
	// ALL(ù ��° ����): �ƹ��� �̸�.�ƹ��� Ȯ����
	// Tile(�� ��° ����): �ƹ��� �̸�.tile
	ofn.nFilterIndex = 0; // ���� �⺻��(0 = ù ��° ����)
	ofn.lpstrFileTitle = nullptr; // â Ÿ��Ʋ �̸�.
	ofn.nMaxFileTitle = 0; // Ÿ��Ʋ �̸� ������.
	
	// �ʱ� ���.(������ �� �⺻������ ������ ���)
	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();

	// ���� ���� ��, ���� �޽����� ǥ���� ����.
	// �������� �ʴ� ��� �Է� or �������� �ʴ� ���� �̸� �Է�.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // (��ũ�� ���)

	// Modal ��� ��Ŀ��. Dialog.
	if (GetSaveFileName(&ofn)) // â ���� �Լ�.
	{ // ���� �� Ȯ�� ��ư�� ���� ����.
		// szName ���� ����ڰ� UI ���� �Է��� ���� �̸��� ���� �������� ��θ� �����.
		SaveTile(szName); // �� �Լ��� ȣ���Ͽ� ��θ� ����.
			              // ������ �����͸� �����ϴ� ����� �� �Լ� ������ ����.
	}
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	// Ŀ�� ������Ʈ.
	FILE* pFile = nullptr;
	
	// ���� ����� �Լ�.
	// ���̳ʸ� ���� ����.
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");

	// ���� ���� üũ.
	assert(pFile);

	// ������ ����.
	
	// Ÿ�� ���� �� ���� ���� ����.
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	// ������ �ּ�, ������ ũ��, ������ ����, ����

	// ��� Ÿ�ϵ��� ���������� ������ �����͸� �����ϰ� ��.
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	// ���� �ݱ�.
	fclose(pFile);
}

void CScene_Tool::LoadtileData()
{
	wchar_t szName[256] = {}; // �������� ���� ��� �迭.(���� ���)

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME); // ����ü ������ ����.
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd(); // �θ� ������ ����.
	ofn.lpstrFile = szName; // ���� ��� �迭�� ���� �ּ�.
	ofn.nMaxFile = sizeof(szName); // �迭�� ������.
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0"; // ���Ϳ� ���� Ȯ���� ����.
	ofn.nFilterIndex = 0; // ���� �⺻��(0 = ù ��° ����)
	ofn.lpstrFileTitle = nullptr; // â Ÿ��Ʋ �̸�.
	ofn.nMaxFileTitle = 0; // Ÿ��Ʋ �̸� ������.

	// �ʱ� ���
	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();

	// ���� �޽����� ǥ���� ����.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // (��ũ�� ���)

	// Modal ��� ��Ŀ��. Dialog.
	if (GetOpenFileName(&ofn)) // â ���� �Լ�.
	{
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName); // ��� ��η� ��ȯ.(LoadTile ������ ��� ��ΰ� ����.)
		LoadTile(strRelativePath); // ��� ����.
	}
}

// �� ��ȯ ��û �Լ�.
void ChangeScene(DWORD_PTR, DWORD_PTR) // �� �Լ��� ���ڰ� �ǹ� ������, ������ �Լ� ��������
{                                      // ������ ����� �ϹǷ�, ��� �̸� ���� �Ű������� �ۼ���.
	ChangeScene(SCENE_TYPE::START);
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