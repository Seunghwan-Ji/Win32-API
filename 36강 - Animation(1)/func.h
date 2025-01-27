#pragma once

class CObject;

// 오브젝트 생성 이벤트.
void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);

// 오브젝트 삭제 이벤트.
void DeleteObject(CObject* _pObj);

// 씬 전환 이벤트.
void ChangeScene(SCENE_TYPE _eNext);

// 지정 그룹 내 벡터 내부를 비우는 함수.
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

// 지정한 map 내부를 비우는 함수.
template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();
	// 템플릿 내에서 inner 클래스 사용시, 앞에 typename 키워드를 붙여줘야 한다.(문법)

	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	_map.clear();
}