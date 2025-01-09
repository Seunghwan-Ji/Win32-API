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
	// �� ���� ����.
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
	// Scene ����.
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	/*m_arrScene:
	�� ��Ұ� CScene �������� �迭.
	���� �� ��ҿ� CScene Ÿ���� �ּҸ� �־��ָ� ��.

	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start :
	'START' �ε��� ��ҿ�, CScene Ÿ�����κ��� ��ӹ��� CScene_Start Ÿ����
	���� �Ҵ��� �޸� ������ �ּҸ� ����.

	m_arrScene �迭�� ��Ҵ� CScene ������ ������, CScene Ÿ���� �ּҸ�
	����Ű�� �ʴ� ���¿�����, CScene_Start Ÿ������ ���� �Ҵ�� �ּҸ� ���� �������ν�,
	'START' �ε����� �ش��ϴ� ��Ҵ� CScene Ÿ���� �ּҸ� ����Ű�� �Ǿ���.*/

	// m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_TOOL];
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_STAGE_01;
	// m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_STAGE_02;

	// ���� �� ����.
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
