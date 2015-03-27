#include<Windows.h>
#include<tchar.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void setPressedButtonsText(TCHAR* text, WPARAM wParam);


INT WINAPI WinMain(HINSTANCE hInst,//Дескриптор данного приложения
	HINSTANCE hPrev,//Дескриптор приложения, которое вызвало наше приложение
	LPSTR lpszCmdLine, //Аргументы коммандной строки
	int nCmdShow
	) {

	//Создание и описание класса окна
	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(wndClass); //Задаем размер структуры WNDCLASSEX
	wndClass.style = CS_HREDRAW | CS_VREDRAW; //Задаем необходимость перерисовки окна при перемещении по горизонтали и вертикали 
	wndClass.cbClsExtra = 0; //Используется ОС
	wndClass.cbWndExtra = 0; //Используется ОС
	wndClass.hInstance = hInst; //Задаем дескриптор нашего приложения нашему окну
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Загружаем стандартную иконку для окна
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //Загрузка стрелочки как курсора окна
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //Задаем белый фон
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
		TEXT("Мое первое окно"),
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
		x = LOWORD(lParam); //получение координаты Х курсора
		y = HIWORD(lParam); //получение координаты Y курсора
		wsprintf(text, TEXT("X = %d, Y = %d"), x, y); //формирование сообщения
		setPressedButtonsText(text, wParam);
		SetWindowText(hwnd, text); //выводим сообщение в заголовок окна
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