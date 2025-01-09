#include "pch.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	// 씬 전부 삭제.
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneMgr::init()
{
	// Scene 생성.
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	/*m_arrScene:
	각 요소가 CScene 포인터인 배열.
	따라서 각 요소엔 CScene 타입의 주소를 넣어주면 됨.

	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start :
	'START' 인덱스 요소에, CScene 타입으로부터 상속받은 CScene_Start 타입을
	동적 할당한 메모리 영역의 주소를 전달.

	m_arrScene 배열의 요소는 CScene 포인터 이지만, CScene 타입의 주소를
	가리키지 않던 상태였으며, CScene_Start 타입으로 동적 할당된 주소를 전달 해줌으로써,
	'START' 인덱스에 해당하는 요소는 CScene 타입의 주소를 가리키게 되었다.*/

	// m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_TOOL];
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_STAGE_01;
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_STAGE_02;

	// 현재 씬 지정.
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}
