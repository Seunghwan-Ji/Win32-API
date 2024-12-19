// TIL.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "TIL.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
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

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TIL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);// ������ ���� ���.

    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    // ����Ű ���̺� ���� �ε�
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TIL));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
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
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.

// ���콺 ��ǥ Ȯ�ο�
int g_x = 0; // x ��ǥ.
int g_y = 0; // y ��ǥ.

POINT g_ptObjPos = { 500, 300 }; // ������ â ������ ������Ʈ�� ��ǥ.
POINT g_ptObjScale = { 100, 100 }; // ������Ʈ�� ũ��.
// POINT: x, y ��� ��� ������ ���� �ְ�, ���� long �ڷ���, ����ü

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // �޴� ������ ���� �м��մϴ�:
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
    case WM_PAINT: // ��ȿȭ ����(Invalidate)�� �߻��� ���.
        // ������ â�� �ּ�ȭ�ǰ� �ٽ� ���� ��Ȳ.
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps); // Device Context(Ŀ�� ������Ʈ) ��ü��
        // ���� ���� ������ ID ��.
        // �տ� H �� ������ ������ �ڵ��̶��
        // Ŀ�� ������Ʈ�̴�.
        // ex) HDC, HPEN, HBRUSH..(int �ڷ��� �ϳ���
        // ����� ���� �ִ� ����ü���̴�.)

// DC(Device Context): ������ â ȭ�鿡 �׸��� �۾� ���࿡ �ʿ��� ������ ����.
// DC �� �������� hwnd
// DC �� ���� �⺻��(Black)
// DC �� �귯���� �⺻ �귯��(White)

// FHD �ػ� ������� ��� �� 1920 * 1080 �� �ȼ� ���� ���´�.
// ȭ���� ��� �ȼ��� �޸� ���� ���¸� ���� �ִ�.
// �ȼ� �� ĭ�� 1����Ʈ ������ �� ����, �� 3����Ʈ�� ũ�⸦ ���´�.
// ������ 256������ �������� ����(�� 1600�� ȭ��), �̸� RGB ��� �θ���.

// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...

// ���� ���� ���� DC �� ����.
        HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // �Ǽ�, ����, �÷�
        // RGB �� ���� �޸��� ������ B G R.
        // R �ڸ��� 255�� ��Ʈ�� ���� �ְ�, G �ڸ��� 0�� ��Ʈ�� ��Ʈ �����ڸ� �����
        // �������� 8ĭ �̵����� �������.
        // ���������� B �ڸ��� 0�� ��Ʈ�� �������� 16ĭ �̵����� �������.
        // �� ��Ʈ ��� '|' �����ڸ� ����� ��Ʈ�� ��ġ�� �ʰ� ��ħ.

        // ���� �귯���� ���� DC �� ����.
        HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
        // HBRUSH hBlueBrush = GetStockObject();
        // GetStockObject: ����ڰ� ���� ���� ��� �귯�� ���� ���� os ���� ������ ���µ�,
        // �̷� ����� ������Ʈ�� �������� �Լ��̴�.
        // ���������� ����� ������Ʈ�̱� ������ ����ڰ� ������ ���Ѵ�.
        // Create Ű���尡 ���� ������Ʈ�� ����ڰ� ���� ���� ������Ʈ�̱� ������ ���� ����.

        // �⺻ �� ID ���� �޾Ƶ�.
        HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);
        // SelectObject �Լ��� ��ȯŸ���� void �̱� ������ ����ڰ� ���� ���� Ÿ�Կ� �°� ĳ������.

        // �⺻ �귯�� ID ���� �޾Ƶ�.
        HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

        // ����� ��� �귯���� �簢�� �׸���.
        // Rectangle(hdc, 10, 10, 110, 110);
        // �»��(10, 10) ��ǥ���� ���ϴ�(110, 100) ��ǥ���� �簢�� �׸���.

        // ���ϴ� ��ġ�� ����� ���� ������Ʈ �׸���.
        Rectangle(hdc
            , g_ptObjPos.x - g_ptObjScale.x / 2
            , g_ptObjPos.y - g_ptObjScale.y / 2
            , g_ptObjPos.x + g_ptObjScale.x / 2
            , g_ptObjPos.y + g_ptObjScale.y / 2);
        // �簢�� ��ġ�� ������Ʈ�� �߽� ��ġ�� �׸���.

        // DC �� ��� �귯���� ���� ������ �ǵ���.
        SelectObject(hdc, hDefaultPen);
        SelectObject(hdc, hDefaultBrush);

        // �� �� ��� �귯�� ���� ��û.(ID ���� ������ ����, OS ���� ID ���� �޾Ƽ� ���� ó����.)
        DeleteObject(hRedPen);
        DeleteObject(hBlueBrush);

        // �׸��� ����.
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_KEYDOWN: // Ű�ٿ� �޽��� Ȯ��.
    {
        switch (wParam) // wParam: Ű���� �Է� �޽���.
        {
        case VK_UP: // �� ����Ű�� ���
            g_ptObjPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
            // ��ȿȭ ���� ���� �߻�.
            // ���� �׸��� �۾��� ��ȿȭ ������ �߻����� ��쿡�� ����ǰ� �ִ�.
            // ��ġ ������Ʈ�� ���� ������ ��ȿȭ ������ �߻���Ų��.
            // �ι�° ���ڴ� �����ε�, null ���� �ָ� ��ü ������ �˻��Ѵ�.
            // ���Ŀ� WM_PAINT �޽����� �߻��ϸ鼭 �ٽ� �׸��� �ȴ�.
            // ����° ���ڴ� true �� �־��ָ� ������ â ȭ�� ��ü�� ���� ��� �ȼ��� Ŭ���� ���ش�.
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

    case WM_LBUTTONDOWN: // ���콺 ��Ŭ�� �޽��� Ȯ��.
    {
        // �Ű����� lParam �� �ڷ����� LPARAM �� ��ü�� long �ڷ����̴�.
        // �� 4����Ʈ ũ�⸦ 2����Ʈ�� ��������, �� �ڸ��� ���콺�� x, y ��ǥ�� ǥ���Ѵ�.
        // 2����Ʈ���̴� �� (65500, 65500)�� ��ǥ���� ��Ÿ�� �� ������, �� ������ �ش��ϴ�
        // �ȼ� ���� ���� �ػ� ����ʹ� ��ǥ�� �дµ� ������ ���� ���̴�.

        // �ߴ����� �ɰ� ������� ���� ������ â �ƹ����� Ŭ���ϰ� ��ǥ Ȯ��.
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
