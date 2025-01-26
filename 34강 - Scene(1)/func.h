#pragma once

class CObject;

// ������Ʈ ���� �̺�Ʈ.
void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);

// ������Ʈ ���� �̺�Ʈ.
void DeleteObject(CObject* _pObj);

// �� ��ȯ �̺�Ʈ.
void ChangeScene(SCENE_TYPE _eNext);

// ���� �׷� �� ���� ���θ� ���� �̺�Ʈ.
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