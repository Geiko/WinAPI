#include<Windows.h>
#include<tchar.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void setPressedButtonsText(TCHAR* text, WPARAM wParam);


INT WINAPI WinMain(HINSTANCE hInst,//���������� ������� ����������
	HINSTANCE hPrev,//���������� ����������, ������� ������� ���� ����������
	LPSTR lpszCmdLine, //��������� ���������� ������
	int nCmdShow
	) {

	//�������� � �������� ������ ����
	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(wndClass); //������ ������ ��������� WNDCLASSEX
	wndClass.style = CS_HREDRAW | CS_VREDRAW; //������ ������������� ����������� ���� ��� ����������� �� ����������� � ��������� 
	wndClass.cbClsExtra = 0; //������������ ��
	wndClass.cbWndExtra = 0; //������������ ��
	wndClass.hInstance = hInst; //������ ���������� ������ ���������� ������ ����
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //��������� ����������� ������ ��� ����
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //�������� ��������� ��� ������� ����
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //������ ����� ���
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = NULL;
	TCHAR lpwszWndClassName[] = _TEXT("MyFirstWindow");
	wndClass.lpszClassName = lpwszWndClassName;
	wndClass.lpfnWndProc = WindowProc;

	if (!RegisterClassEx(&wndClass)){
		return 0;
	}

	HWND hWnd = CreateWindowEx(
		NULL,
		lpwszWndClassName,
		TEXT("��� ������ ����"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL
		);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
TCHAR text[128];
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	INT x;
	INT y;
	switch (msg){
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
		HBRUSH color;
		if (wParam & MK_LBUTTON && wParam & MK_RBUTTON) {
			color = CreateSolidBrush(RGB(255, 0, 0));
		}
		else if (wParam & MK_LBUTTON) {
			color = CreateSolidBrush(RGB(0, 0, 255));
		}
		else if (wParam & MK_RBUTTON) {
			color = CreateSolidBrush(RGB(0, 255, 0));
		}
		else if (wParam & MK_MBUTTON) {
			color = CreateSolidBrush(RGB(255, 255, 0));
		}
		else {
			color = CreateSolidBrush(RGB(255, 255, 255));
		}
		SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)color);
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		//TODO: fix it
		x = LOWORD(lParam); //��������� ���������� � �������
		y = HIWORD(lParam); //��������� ���������� Y �������
		wsprintf(text, TEXT("X = %d, Y = %d"), x, y); //������������ ���������
		setPressedButtonsText(text, wParam);
		SetWindowText(hwnd, text); //������� ��������� � ��������� ����
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

void setPressedButtonsText(TCHAR* text, WPARAM wParam) {
	if (wParam & MK_LBUTTON) {
		lstrcat(text, TEXT(" Left Mouse Click "));
	}
	if (wParam & MK_RBUTTON) {
		lstrcat(text, TEXT(" Right Mouse Click "));
	}
	if (wParam & MK_MBUTTON) {
		lstrcat(text, TEXT(" Middle Mouse Click "));
	}
}