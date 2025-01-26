#pragma once

class CObject;

// 오브젝트 생성 이벤트.
void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);

// 오브젝트 삭제 이벤트.
void DeleteObject(CObject* _pObj);

// 씬 전환 이벤트.
void ChangeScene(SCENE_TYPE _eNext);

// 지정 그룹 내 벡터 내부를 비우는 이벤트.
template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	// 벡터의 요소를 순회하며, 포인터가 가리키는 동적 메모리 삭제.
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}
	// 벡터를 비움.
	_vec.clear();
}