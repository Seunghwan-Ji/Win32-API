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

// 마우스 좌표 확인용
int g_x = 0; // x 좌표.
int g_y = 0; // y 좌표.

POINT g_ptObjPos = { 500, 300 }; // 윈도우 창 내에서 오브젝트의 좌표.
POINT g_ptObjScale = { 100, 100 }; // 오브젝트의 크기.
// POINT: x, y 라는 멤버 변수를 갖고 있고, 각각 long 자료형, 구조체

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
        HDC hdc = BeginPaint(hWnd, &ps); // Device Context(커널 오브젝트) 객체를
        // 만들어서 얻은 윈도우 ID 값.
        // 앞에 H 가 붙은건 윈도우 핸들이라는
        // 커널 오브젝트이다.
        // ex) HDC, HPEN, HBRUSH..(int 자료형 하나를
        // 멤버로 갖고 있는 구조체들이다.)

// DC(Device Context): 윈도우 창 화면에 그리기 작업 수행에 필요한 데이터 집합.
// DC 의 목적지는 hwnd
// DC 의 펜은 기본펜(Black)
// DC 의 브러쉬는 기본 브러쉬(White)

// FHD 해상도 모니터의 경우 총 1920 * 1080 의 픽셀 수를 갖는다.
// 화면의 모든 픽셀은 메모리 공간 형태를 갖고 있다.
// 픽셀 한 칸에 1바이트 공간이 세 개씩, 총 3바이트의 크기를 갖는다.
// 공간당 256가지의 가짓수를 갖고(총 1600만 화소), 이를 RGB 라고 부른다.

// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

// 직접 펜을 만들어서 DC 에 지급.
        HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // 실선, 굵기, 컬러
        // RGB 의 실제 메모리의 구조는 B G R.
        // R 자리에 255의 비트를 먼저 넣고, G 자리에 0의 비트를 비트 연산자를 사용해
        // 좌측으로 8칸 이동시켜 집어넣음.
        // 마지막으로 B 자리에 0의 비트를 좌측으로 16칸 이동시켜 집어넣음.
        // 세 비트 모두 '|' 연산자를 사용해 비트롤 겹치지 않게 합침.

        // 직접 브러쉬를 만들어서 DC 에 지급.
        HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
        // HBRUSH hBlueBrush = GetStockObject();
        // GetStockObject: 사용자가 자주 쓰는 펜과 브러쉬 같은 것을 os 에서 저장해 놓는데,
        // 이런 저장된 오브젝트를 가져오는 함수이다.
        // 내부적으로 저장된 오브젝트이기 때문에 사용자가 지우지 못한다.
        // Create 키워드가 붙은 오브젝트는 사용자가 직접 만든 오브젝트이기 때문에 삭제 가능.

        // 기본 펜 ID 값을 받아둠.
        HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);
        // SelectObject 함수의 반환타입이 void 이기 때문에 사용자가 지역 변수 타입에 맞게 캐스팅함.

        // 기본 브러쉬 ID 값을 받아둠.
        HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

        // 변경된 펜과 브러쉬로 사각형 그리기.
        // Rectangle(hdc, 10, 10, 110, 110);
        // 좌상단(10, 10) 좌표부터 우하단(110, 100) 좌표까지 사각형 그리기.

        // 원하는 위치에 사용자 정의 오브젝트 그리기.
        Rectangle(hdc
            , g_ptObjPos.x - g_ptObjScale.x / 2
            , g_ptObjPos.y - g_ptObjScale.y / 2
            , g_ptObjPos.x + g_ptObjScale.x / 2
            , g_ptObjPos.y + g_ptObjScale.y / 2);
        // 사각형 위치를 오브젝트의 중심 위치에 그린다.

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

    case WM_KEYDOWN: // 키다운 메시지 확인.
    {
        switch (wParam) // wParam: 키보드 입력 메시지.
        {
        case VK_UP: // 윗 방향키일 경우
            g_ptObjPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
            // 무효화 영역 강제 발생.
            // 현재 그리기 작업은 무효화 영역이 발생했을 경우에만 수행되고 있다.
            // 위치 업데이트를 위해 강제로 무효화 영역을 발생시킨다.
            // 두번째 인자는 영역인데, null 값을 주면 전체 영역을 검사한다.
            // 이후에 WM_PAINT 메시지가 발생하면서 다시 그리게 된다.
            // 세번째 인자는 true 를 넣어주면 윈도우 창 화면 전체에 대한 모든 픽셀을 클리어 해준다.
            break;

        case VK_DOWN:
            g_ptObjPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_LEFT:
            g_ptObjPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_RIGHT:
            g_ptObjPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        }
    }
    break;

    case WM_LBUTTONDOWN: // 마우스 좌클릭 메시지 확인.
    {
        // 매개변수 lParam 의 자료형인 LPARAM 의 정체는 long 자료형이다.
        // 총 4바이트 크기를 2바이트씩 나누었고, 각 자리에 마우스의 x, y 좌표를 표현한다.
        // 2바이트씩이니 약 (65500, 65500)의 좌표까지 나타낼 수 있으며, 이 범위에 해당하는
        // 픽셀 수를 가진 해상도 모니터는 좌표를 읽는데 문제가 없을 것이다.

        // 중단점을 걸고 디버깅을 통해 윈도우 창 아무곳을 클릭하고 좌표 확인.
        g_x = LOWORD(lParam);
        g_y = HIWORD(lParam);
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
