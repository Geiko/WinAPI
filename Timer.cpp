#include<Windows.h>
#include<tchar.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
VOID CALLBACK timerProc(HWND hwnd, UINT msg, UINT_PTR wParam, DWORD lParam);
void print(HWND hwnd);


//������������ ���� ��� ���������� ����������
namespace glb {
	//������������� �������
	const INT TIMER_ID = 1;
	//��������� ����� ��� ������������ ������ � ��������� ����
	TCHAR str[128];
	//���������� ��� �������� �������� �������� ������� �������
	UINT time = 0;
	//������� ������������ �������
	const UINT TIMER_SPEED = 1;
}

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

/*
������� ������� ��� ���������, ������� ���������� ������������ �������� ��� ������������ ������ �������
���������:
hwnd	- ���������� ���� � ������� ��������� �������
msg		- ��� ���������
wParam � lParam - ���������, �������� ���� ����� � ����������� �� ����, ����� ������� ���������.
����� �������� � MSDN
*/
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg){
	case WM_LBUTTONDOWN:
		SetTimer(hwnd, glb::TIMER_ID, glb::TIMER_SPEED, timerProc);
		break;
	case WM_RBUTTONDOWN:
		KillTimer(hwnd, glb::TIMER_ID);
		break;
	case WM_MBUTTONDOWN:
		glb::time = 0;
		KillTimer(hwnd, glb::TIMER_ID);
		print(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

VOID CALLBACK timerProc(HWND hwnd, UINT msg, UINT_PTR wParam, DWORD lParam) {
	print(hwnd);
	glb::time++;
}

void print(HWND hwnd){
	INT minutes = glb::time / 60;
	INT seconds = glb::time - minutes * 60;
	wsprintf(glb::str, TEXT("%02d:%02d"), minutes, seconds);
	SetWindowText(hwnd, glb::str);
}
