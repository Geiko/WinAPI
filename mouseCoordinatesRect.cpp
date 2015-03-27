//	2. Предположим, что существует прямоугольник, границы которого на
//	10 пикселей отстоят от границ клиентской области окна.

//	Необходимо при нажатии левой кнопки мыши выводить в заголовок окна
//	сообщение  о  том, где  произошел  щелчок  мышью :
//	внутри прямоугольника, снаружи или на границе прямоугольника.

//	При нажатии правой  кнопки  мыши  необходимо  выводить  в  заголовок  окна
//	информацию о размере клиентской области окна(ширина и высота клиентской области окна).

#include<Windows.h>
#include<tchar.h>

namespace glb {
	int margin = 10;
	TCHAR str[128], inf[128], winInfo[128];
	INT x, y, width, height;
}

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение");  /* Имя класса окна */

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	/* 1. Определение класса окна */
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;

	/* 2. Регистрация класса окна */
	if (!RegisterClassEx(&wcl))
		return 0;

	/* 3. Создание окна */
	hWnd = CreateWindowEx(
		0,
		szClassWindow,
		TEXT("My second window"),
		WS_OVERLAPPEDWINDOW,
		800,
		200,
		500,
		300,
		NULL,
		NULL,
		hInst,
		NULL
		);

	/* 4. Отображение окна */
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	/* 5. Запуск цикла обработки сooбщений */
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);		//ф-ция определения параметров клиентского окна

	switch (uMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:

		glb::x = LOWORD(lParam);					//получение координаты Х курсора
		glb::y = HIWORD(lParam);					//получение координаты Y курсора

		if (glb::x > glb::margin && glb::x < clientRect.right - glb::margin  &&  glb::y > glb::margin && glb::y < clientRect.bottom - glb::margin)
			wcscpy_s(glb::inf, TEXT("IN"));

		else if (glb::x < glb::margin || glb::x > clientRect.right - glb::margin || glb::y < glb::margin || glb::y > clientRect.bottom - glb::margin)
			wcscpy_s(glb::inf, TEXT("OUT"));

		else if (glb::x == glb::margin &&	glb::y > glb::margin && glb::y < clientRect.bottom - glb::margin
			|| glb::x == clientRect.right - glb::margin && glb::y > glb::margin && glb::y < clientRect.bottom - glb::margin
			|| glb::y == glb::margin && glb::x > glb::margin && glb::x < clientRect.right - glb::margin
			|| glb::y == clientRect.bottom - glb::margin && glb::x > glb::margin && glb::x < clientRect.right - glb::margin)
			wcscpy_s(glb::inf, TEXT("BORDER"));

		wsprintf(glb::str, TEXT("%s"), glb::inf);
		SetWindowText(hWnd, glb::str);			// изменяем заголовок окна на нашу информацию
		break;

	case WM_RBUTTONDOWN:
		glb::width = clientRect.right;
		glb::height = clientRect.bottom;
		wsprintf(glb::winInfo, TEXT("width: %d        height: %d"), glb::width, glb::height);
		SetWindowText(hWnd, glb::winInfo);			// изменяем заголовок окна на нашу информацию
		break;

	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}