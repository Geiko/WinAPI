#include<Windows.h>
#include<tchar.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
VOID CALLBACK timerProc(HWND hwnd, UINT msg, UINT_PTR wParam, DWORD lParam);
void print(HWND hwnd);


//Пространство имен для глобальных переменных
namespace glb {
	//Идентификатор таймера
	const INT TIMER_ID = 1;
	//Строковый буфер для формирования текста в заголовке окна
	TCHAR str[128];
	//Переменная для хранения текущего значения времени таймера
	UINT time = 0;
	//частота срабатывания таймера
	const UINT TIMER_SPEED = 1;
}

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

/*
Оконная функция или процедура, которая вызывается операционной системой при срабатывании любого события
Принимает:
hwnd	- дескриптор окна в котором произошло событие
msg		- код сообщения
wParam и lParam - аргументы, меняющие свой смысл в зависимости от того, какое событие произошло.
смысл смотреть в MSDN
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
