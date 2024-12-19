// TIL.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "TIL.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_     HINSTANCE hInstance
    , _In_opt_ HINSTANCE hPrevInstance
    , _In_     LPWSTR    lpCmdLine
    , _In_     int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TIL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);// 윈도우 정보 등록.

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TIL));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TIL));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TIL);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.

#include <vector>
using std::vector;

struct tObjInfo
{
    POINT g_ptObjPos; // 윈도우 창 내에서 오브젝트의 좌표.
    POINT g_ptObjScale; // 오브젝트의 크기.
};

vector<tObjInfo> g_vecInfo; // 가변 배열 객체 생성.

// 좌 상단 좌표.
POINT g_ptLT;

// 우 하단 좌표.
POINT g_ptRB;

bool bLbtnDown = false; // 마우스 클릭 여부에 활용할 전역 변수.

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT: // 무효화 영역(Invalidate)이 발생한 경우.
        // 윈도우 창이 최소화되고 다시 켜진 상황.
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        // 직접 펜을 만들어서 DC 에 지급.
        HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // 실선, 굵기, 컬러

        // 직접 브러쉬를 만들어서 DC 에 지급.
        HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

        // 기본 펜 ID 값을 받아둠.
        HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);

        // 기본 브러쉬 ID 값을 받아둠.
        HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

        // 원하는 위치에 사용자 정의 오브젝트 그리기.
        if (bLbtnDown)
        {
            Rectangle(hdc
                , g_ptLT.x, g_ptLT.y
                , g_ptRB.x, g_ptRB.y);
        }

        // 벡터에 저장된 오브젝트 그리기.
        for (size_t i = 0; i < g_vecInfo.size(); ++i)
        {
            Rectangle(hdc
                , g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x / 2
                , g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2
                , g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2
                , g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2);
        }

        // DC 의 펜과 브러쉬를 원래 것으로 되돌림.
        SelectObject(hdc, hDefaultPen);
        SelectObject(hdc, hDefaultBrush);

        // 다 쓴 펜과 브러쉬 삭제 요청.(ID 값을 보내는 개념, OS 에서 ID 값을 받아서 삭제 처리함.)
        DeleteObject(hRedPen);
        DeleteObject(hBlueBrush);

        // 그리기 종료.
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_LBUTTONDOWN: // 마우스 좌클릭 메시지 확인.
    {
        g_ptLT.x = LOWORD(lParam);
        g_ptLT.y = HIWORD(lParam);
        bLbtnDown = true; // 마우스 클릭 활성화.
    }
    break;

    case WM_MOUSEMOVE:
    {
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);
    }
    break;

    case WM_LBUTTONUP:
    {
        tObjInfo info = {};
        // 오브젝트의 중심 좌표 계산.( (좌 상단 + 우 하단) / 2 )
        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        // 오브젝트의 크기 절댓값 계산.( (좌 상단 - 우 하단)의 절댓값 )
        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info); // 벡터에 오브젝트 저장.
        bLbtnDown = false; // 마우스 클릭 비활성화.
        InvalidateRect(hWnd, nullptr, true);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}