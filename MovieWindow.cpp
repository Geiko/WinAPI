#include<Windows.h>
#include<tchar.h>
//макрос проверки на нажатие стрелочки на клавиатуре
#define IS_ARROW_PRESSED(wParam) (wParam == VK_UP || wParam == VK_DOWN || wParam == VK_LEFT || wParam == VK_RIGHT) 

namespace glb {
	TCHAR str[128];
	RECT windowRect{};
	int step = 60;
	int height = 100;
	int width = 200;
	int resolutionX = 1280;
	int resolutionY = 1024;
	const int SPEED = 10; //чем меньше - тем быстрее
	const int START_X = 0;
	const int START_Y = 0;
	HWND hOtherWindow;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



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

	glb::hOtherWindow = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
	if (glb::hOtherWindow == NULL) {
		glb::hOtherWindow = hWnd;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MoveWindow(hWnd, glb::START_X, glb::START_Y, glb::width, glb::height, TRUE);
	MSG msg;
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

void lButtonClick(HWND hwnd);
void rButtonClick(HWND hwnd);
void windowStep(HWND hwnd, WPARAM wParam);
void stepUp(HWND hwnd);
void stepDown(HWND hwnd);
void stepLeft(HWND hwnd);
void stepRight(HWND hwnd);


LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	using namespace glb;
	switch (msg){
	case WM_LBUTTONDOWN:
		lButtonClick(hwnd);
		break;
	case WM_RBUTTONDOWN:
		rButtonClick(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (IS_ARROW_PRESSED(wParam)) {
			windowStep(glb::hOtherWindow, wParam);
		}

		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

void lButtonClick(HWND hwnd) {
	using namespace glb;
	GetWindowRect(hwnd, &windowRect);
	wsprintf(glb::str, TEXT("left = %d, top = %d, bottom = %d, right = %d"),
		windowRect.left, windowRect.top, windowRect.bottom, windowRect.right);

	MessageBox(hwnd, str, TEXT("Rect"), MB_OK | MB_ICONINFORMATION);
	GetClientRect(hwnd, &windowRect);
	wsprintf(str, TEXT("left = %d, top = %d, bottom = %d, right = %d"),
		windowRect.left, windowRect.top, windowRect.bottom, windowRect.right);

	MessageBox(hwnd, str, TEXT("Client Rect"), MB_OK | MB_ICONINFORMATION);
}

void rButtonClick(HWND hwnd) {
	using namespace glb;
	MoveWindow(hwnd, START_X, START_Y, width, height, TRUE);
	for (int i = 0; i < (resolutionX - width) / step; i++) {
		GetWindowRect(hwnd, &windowRect);
		for (int j = 0; j < step; j++) {
			MoveWindow(hwnd, windowRect.left, START_Y, width + j, height, TRUE);
			Sleep(SPEED);
		}
		for (int j = 0; j < step; j++) {
			MoveWindow(hwnd, windowRect.left + j, START_Y, width + step - j, height, TRUE);
			Sleep(SPEED);
		}
	}
}

void windowStep(HWND hwnd, WPARAM wParam){
	switch (wParam) {
	case VK_UP:
		stepUp(hwnd);
		break;
	case VK_DOWN:
		stepDown(hwnd);
		break;
	case VK_LEFT:
		stepLeft(hwnd);
		break;
	case VK_RIGHT:
		stepRight(hwnd);
		break;

	}
}
void stepUp(HWND hwnd) {
	using namespace glb;
	GetWindowRect(hwnd, &glb::windowRect);

	for (int j = 0; j < step; j++) {
		MoveWindow(hwnd, windowRect.left, windowRect.top, width, height - j, TRUE);
		Sleep(SPEED);
	}
	for (int j = 0; j < step; j++) {
		MoveWindow(hwnd, windowRect.left, windowRect.top - j, width, height - step + j, TRUE);
		Sleep(SPEED);
	}
}

void stepDown(HWND hwnd) {
	using namespace glb;
	GetWindowRect(hwnd, &glb::windowRect);

	for (int j = 0; j < step; j++) {
		MoveWindow(hwnd, windowRect.left, windowRect.top, width, height + j, TRUE);
		Sleep(SPEED);
	}
	for (int j = 0; j < step; j++) {
		MoveWindow(hwnd, windowRect.left, windowRect.top + j, width, height + step - j, TRUE);
		Sleep(SPEED);
	}

}
void stepLeft(HWND hwnd) {
	using namespace glb;
	GetWindowRect(hwnd, &glb::windowRect);

	for (int j = 0; j < step; j++) {
		MoveWindow(hwnd, windowRect.left, windowRect.top, width - j, height, TRUE);
		Sleep(SPEED);
	}
	for (int j = 0; j < step; j++) {
		MoveWindow(hwnd, windowRect.left - j, windowRect.top, width - step + j, height, TRUE);
		Sleep(SPEED);
	}

}


void stepRight(HWND hwnd) {
	using namespace glb;
	GetWindowRect(hwnd, &glb::windowRect);

	for (int j = 0; j < step; j++) {
		MoveWindow(hwnd, windowRect.left, windowRect.top, width + j, height, TRUE);
		Sleep(SPEED);
	}
	for (int j = 0; j < step; j++) {
		MoveWindow(hwnd, windowRect.left + j, windowRect.top, width + step - j, height, TRUE);
		Sleep(SPEED);
	}
}