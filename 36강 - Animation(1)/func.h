#pragma once

class CObject;

// ������Ʈ ���� �̺�Ʈ.
void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);

// ������Ʈ ���� �̺�Ʈ.
void DeleteObject(CObject* _pObj);

// �� ��ȯ �̺�Ʈ.
void ChangeScene(SCENE_TYPE _eNext);

// ���� �׷� �� ���� ���θ� ���� �Լ�.
template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	// ������ ��Ҹ� ��ȸ�ϸ�, �����Ͱ� ����Ű�� ���� �޸� ����.
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}
	// ���͸� ���.
	_vec.clear();
}

// ������ map ���θ� ���� �Լ�.
template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();
	// ���ø� ������ inner Ŭ���� ����, �տ� typename Ű���带 �ٿ���� �Ѵ�.(����)

	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	_map.clear();
}