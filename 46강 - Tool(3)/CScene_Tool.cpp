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
	// 타일 생성.
	CreateTile(5, 5);

	// Camera Look 지정.
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
		// 클릭한 마우스 좌표.
		Vec2 vMousePos = MOUSE_POS;

		// 실제 좌표로 변환.
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		// 가로, 세로 타일 개수.
		UINT iTileX = GetTileX();
		UINT iTileY = GetTileY();

		// 마우스의 좌표를 타일 하나의 사이즈로 나누어 행, 열 번호를 알아냄.
		UINT iCol = (UINT)vMousePos.x / TILE_SIZE;
		UINT iRow = (UINT)vMousePos.y / TILE_SIZE;

		// 타일 그룹은 1차원 벡터 이므로, 2차원 행렬 인덱스를 1차원 인덱스로 계산.
		UINT iIdx = iRow * iTileX + iCol;
		// 1. 한 행은 가로의 전체 타일 수를 포함.
		// 2. 남은 타일 수는 열 번호와 동일.

		// 타일 그룹에 인덱싱.
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx(); // 타일 오브젝트의 이미지 인덱스 증가.
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
			// 리소스 뷰에서 타일 개수 입력란을 우클릭 후, 속성에서 '숫자' 부분을 True 로 변경하면,
			// 타일 개수 입력란에 숫자만 입력할 수 있다.

			// GetDlgItemInt: 입력한 숫자 텍스트를 정수 값으로 가져오는 함수.
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			// 현재 씬 확인.
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// ToolScene 인지 확인.(다운캐스팅 시도)
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			// 기존 타일 오브젝트 삭제.
			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			
			// 새 타일 오브젝트 생성.
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			// EndDialog 함수는 반환 값이 존재하며, 지역 변수로 받을 경우,
			// 두번째 인자의 값을 받는다.
			// 값은 IDOK 또는 IDCANCEL 이다.
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