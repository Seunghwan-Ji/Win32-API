#pragma once

class CTexture;

// 싱글톤 패턴
// 객체의 생성을 1개로 제한.
// 어디서든 쉽게 접근 가능.

class CCore
{
	SINGLE(CCore); // define 헤더 파일의 매크로 활용.

private:
	HWND	  m_hWnd;		  // 메인 윈도우 핸들.
	POINT	  m_ptResolution; // 메인 윈도우 해상도.
	HDC		  m_hDC;	      // 메인 윈도우에 Draw 할 DC.

	CTexture* m_pMemTex;      // 백버퍼 텍스처.

	// 자주 사용하는 GDI object
	HBRUSH    m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN      m_arrPen[(UINT)PEN_TYPE::END];

	// 메뉴.
	HMENU     m_hMenu; // Tool Scene 에서만 사용.

public:
	int Init(HWND _hWnd, POINT _ptResolution); // 윈도우 초기화 함수.
	void progress(); // 비동기식 프로그램에서 메시지가 발생하지 않는 동안 실행할 함수.

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hWnd; }			 // 메인 윈도우 핸들 반환 함수.
	HDC GetMainDC() { return m_hDC; }				 // 메인 윈도우 DC 반환 함수.
	HMENU GetMenu() { return m_hMenu; }				 // 메뉴 반환 함수.

	POINT GetResolution() { return m_ptResolution; } // 해상도 반환 함수.
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};