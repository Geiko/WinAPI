//	1. Написать приложение, в котором ведётся подсчёт количества «кликов» 
//	левой, правой и средней кнопки мыши. Обновляемую статистику необходимо 
//	выводить в заголовок окна.

#include<Windows.h>
#include<tchar.h>

namespace glb {
	int counterLButton = 0;
	int counterRButton = 0;
	int counterMButton = 0;
	TCHAR mouseInfo[128];
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
		TEXT("My first window"),
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
	switch (uMessage)
	{
	case WM_LBUTTONDOWN:
		glb::counterLButton++; 
		break;
	case WM_RBUTTONDOWN:
		glb::counterRButton++;
		break;
	case WM_MBUTTONDOWN:
		glb::counterMButton++;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}

	wsprintf(glb::mouseInfo, TEXT("left button: %d        middle button: %d       right button: %d"), glb::counterLButton, glb::counterMButton, glb::counterRButton);
	SetWindowText(hWnd, glb::mouseInfo);			// изменяем заголовок окна на нашу информацию

	return 0;
}