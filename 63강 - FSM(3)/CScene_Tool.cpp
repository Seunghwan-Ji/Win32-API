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
	// 툴 Scene 에서 사용할 메뉴를 붙인다.
	CCore::GetInst()->DockMenu();

	// 타일 생성.
	CreateTile(5, 5);

	// UI 하나 만들어보기.
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// 윈도우 창 우상단에 배치.

	// 부모 UI 오브젝트 생성.
	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 150.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

	// 자식 UI 오브젝트 생성.
	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(30.f, 20.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));

	// 이 UI 에 대한 콜백 함수 세팅.
	((CBtnUI*)pBtnUI)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SaveTileData);
	// (SCENE_MEMFUNC): 함수 포인터에서 정의한 멤버 함수 타입으로 명시적인 캐스팅을 해줘야한다.
	
	pPanelUI->AddChild(pBtnUI); // 부모 UI 에 자식 UI 추가.

	AddObject(pPanelUI, GROUP_TYPE::UI); // 부모 UI 를 추가 함으로써 자식 UI 가 같이 추가됨.

	// UI 복사.
	// CUI* pClonePanel = pPanelUI->Clone();
	// pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
	
	// 복사본 UI 의 자식 UI 쪽에 콜백 함수 세팅.
	// ((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClikedCallBack(ChangeScene, 0, 0);
	
	// AddObject(pClonePanel, GROUP_TYPE::UI);

	// 단축키로 포커싱 할 UI.
	// m_pUI = pClonePanel;

	// Camera Look 지정.
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

	// 왼쪽 쉬프트 키를 누르면 파일 저장.
	// if (KEY_TAP(KEY::LSHIFT))
	// {
	// 	// CUIMgr::GetInst()->SetFocusedUI(m_pUI);
	// 	SaveTileData();
	// }

	// 컨트롤 키를 누르면 파일 불러와서 읽기.
	if (KEY_TAP(KEY::CTRL))
	{
		LoadtileData();
	}
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
		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		// 마우스의 좌표를 타일 하나의 사이즈로 나누어 행, 열 번호를 알아냄.
		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		// 타일이 아닌 곳을 클릭 했을 경우 예외 처리.
		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		// 타일 그룹은 1차원 벡터 이므로, 2차원 행렬 인덱스를 1차원 인덱스로 계산.
		UINT iIdx = iRow * iTileX + iCol;
		// 1. 한 행은 가로의 전체 타일 수를 포함.
		// 2. 남은 타일 수는 열 번호와 동일.

		// 타일 그룹에 인덱싱.
		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx(); // 타일 오브젝트의 이미지 인덱스 증가.
	}
}

void CScene_Tool::SaveTileData()
{
	wchar_t szName[256] = {}; // 최종적인 파일 경로 배열.(절대 경로)

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME); // 구조체 사이즈 지정.
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd(); // 부모 윈도우 지정.
	ofn.lpstrFile = szName; // 파일 경로 배열의 시작 주소.
	ofn.nMaxFile = sizeof(szName); // 배열의 사이즈.
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0"; // 필터와 파일 확장자 설정.
	// ALL(첫 번째 필터): 아무런 이름.아무런 확장자
	// Tile(두 번째 필터): 아무런 이름.tile
	ofn.nFilterIndex = 0; // 필터 기본값(0 = 첫 번째 필터)
	ofn.lpstrFileTitle = nullptr; // 창 타이틀 이름.
	ofn.nMaxFileTitle = 0; // 타이틀 이름 사이즈.
	
	// 초기 경로.(저장할 시 기본적으로 들어와질 경로)
	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();

	// 파일 저장 시, 오류 메시지를 표시할 조건.
	// 존재하지 않는 경로 입력 or 존재하지 않는 파일 이름 입력.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // (매크로 상수)

	// Modal 방식 포커싱. Dialog.
	if (GetSaveFileName(&ofn)) // 창 여는 함수.
	{ // 저장 시 확인 버튼을 누른 상태.
		// szName 에는 사용자가 UI 에서 입력한 파일 이름에 대한 최종적인 경로를 저장됨.
		SaveTile(szName); // 이 함수를 호출하여 경로를 전달.
			              // 실제로 데이터를 저장하는 기능은 이 함수 내에서 구현.
	}
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	// 커널 오브젝트.
	FILE* pFile = nullptr;
	
	// 파일 입출력 함수.
	// 바이너리 모드로 쓰기.
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");

	// 파일 실패 체크.
	assert(pFile);

	// 데이터 저장.
	
	// 타일 가로 및 세로 개수 저장.
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	// 데이터 주소, 데이터 크기, 데이터 개수, 파일

	// 모든 타일들을 개별적으로 저장할 데이터를 저장하게 함.
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	// 파일 닫기.
	fclose(pFile);
}

void CScene_Tool::LoadtileData()
{
	wchar_t szName[256] = {}; // 최종적인 파일 경로 배열.(절대 경로)

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME); // 구조체 사이즈 지정.
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd(); // 부모 윈도우 지정.
	ofn.lpstrFile = szName; // 파일 경로 배열의 시작 주소.
	ofn.nMaxFile = sizeof(szName); // 배열의 사이즈.
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0"; // 필터와 파일 확장자 설정.
	ofn.nFilterIndex = 0; // 필터 기본값(0 = 첫 번째 필터)
	ofn.lpstrFileTitle = nullptr; // 창 타이틀 이름.
	ofn.nMaxFileTitle = 0; // 타이틀 이름 사이즈.

	// 초기 경로
	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();

	// 오류 메시지를 표시할 조건.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // (매크로 상수)

	// Modal 방식 포커싱. Dialog.
	if (GetOpenFileName(&ofn)) // 창 여는 함수.
	{
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName); // 상대 경로로 전환.(LoadTile 에서는 상대 경로가 쓰임.)
		LoadTile(strRelativePath); // 경로 전달.
	}
}

// 씬 전환 요청 함수.
void ChangeScene(DWORD_PTR, DWORD_PTR) // 이 함수는 인자가 의미 없지만, 정의한 함수 포인터의
{                                      // 구조를 따라야 하므로, 대신 이름 없는 매개변수로 작성함.
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