#include "pch.h"
#include "CTexture.h"

CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP
		, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	// 1. nullptr
	// ���ҽ� �ڵ�. ���⼭�� nullptr�� �����Ͽ� ���ø����̼� ���ҽ��� �ƴ� �ܺ� ���Ͽ��� �̹�����
	// �ε��ϰڴٴ� ���� ��Ÿ���ϴ�.

	// 2. _strFilePath.c_str()
	// _strFilePath�� wstring Ÿ������ ���޵Ǹ�, .c_str()�� ���� const wchar_t*�� ��ȯ�Ͽ� ����
	// ��θ� API�� �����մϴ�.

	// 3. IMAGE_BITMAP
	// �ҷ��� ���ҽ� ������ �����մϴ�. ���⼭�� ��Ʈ�� �̹����� �ǹ��մϴ�.

	// 4. 0, 0
	// �̹����� �ε��� �� ����� �ʺ�� ���̸� �����մϴ�. 0���� �����ϸ� �⺻ ũ��� �ε��մϴ�.

	// 5. LR_CREATEDIBSECTION | LR_LOADFROMFILE
	// �ε� �ɼ��� �����ϴ� �÷����Դϴ�:
	// - LR_CREATEDIBSECTION
	//	 ��Ʈ�� �����Ϳ� ���� ������ �� �ִ� �޸� ���� ��ü�� �����մϴ�.
	// - LR_LOADFROMFILE
	//   ������ ���� ��ο��� �̹����� �ε��մϴ�.

	// �Լ� ��ȯ Ÿ��
	// LoadImage�� ��ȯ������ HANDLE�� �����մϴ�.
	// HANDLE�� Windows API���� �پ��� ���ҽ�(����, ��Ʈ��, ������ ��)�� �ڵ��� �����ϴ� �Ϲ�����
	// Ÿ���Դϴ�.
	// ��ȯ�� HANDLE�� ȣ���� ���ҽ��� ������ ���� ������ Ưȭ�� �ڵ� Ÿ������ ��ȯ�Ͽ� ����ؾ�
	// �մϴ�.
	// (HBITMAP) �� ��ȯ�� �����Ϸ����� "�� �ڵ��� ��Ʈ������ ����� ��"���� �˸��� ��Ȯ�� ��ȣ��
	// �ݴϴ�.

	assert(m_hBit); // �̹��� �ε尡 �����ϸ� ����ó��.
}