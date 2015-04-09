//	6. Написать  приложение, обладающее  следующей    функциональностью:
//
//	-  при нажатии клавиши <Enter> главное окно позиционируется
//	в левый верхний угол экрана с размерами(300х300) и начинает
//	перемещаться  по  периметру  экрана  с  определённой скоростью;
//
//	-  при нажатии клавиши <Esc> перемещение окна прекращается.

#include <windows.h> 
#include "tchar.h"

namespace glb {
	TCHAR str[128];
	INT t = 0, width = 350, height = 300, x = 0, y = 0, step = 2000, stepSpan = 1;
	INT screenX, screenY, screenWidth, screenHeight;
	INT horizontalMove, verticalMove;
}

void WindowStep(HWND hWnd);

//прототип оконной процедуры 
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение");  /* Имя класса окна */

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine,	int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	/* 1. Определение класса окна  */

	wcl.cbSize = sizeof(wcl);  // размер структуры WNDCLASSEX  
	// Перерисовать всё окно, если изменён размер по горизонтали  
	// или по вертикали 
	wcl.style = CS_HREDRAW | CS_VREDRAW; // CS(Class Style) - стиль класса окна 
	wcl.lpfnWndProc = WindowProc; // адрес оконной процедуры 
	wcl.cbClsExtra = 0;  // используется Windows  
	wcl.cbWndExtra = 0;   // используется Windows  
	wcl.hInstance = hInst;  // дескриптор данного приложения 

	// загрузка стандартной иконки 
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	// загрузка стандартного курсора 
	wcl.hCursor = LoadCursor(NULL, IDC_WAIT);

	// заполнение окна белым цветом     
	wcl.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wcl.lpszMenuName = NULL;  //приложение не содержит меню 
	wcl.lpszClassName = szClassWindow;  //имя класса окна 
	wcl.hIconSm = NULL; // отсутствие маленькой иконки 

	/*  2. Регистрация класса окна  */

	if (!RegisterClassEx(&wcl))
		return 0; // при неудачной регистрации - выход 

	/*  3. Создание окна  */

	// создается окно и  переменной hWnd присваивается дескриптор окна 
	hWnd = CreateWindowEx(
		0,    // расширенный стиль окна 
		szClassWindow,  // имя класса окна 
		TEXT("My first window."), // заголовок окна 
		WS_THICKFRAME,  // стиль окна 
		/* Заголовок, рамка, позволяющая менять размеры, системное меню,
		кнопки развёртывания и свёртывания окна  */
		CW_USEDEFAULT,  // х-координата левого верхнего угла окна 
		CW_USEDEFAULT,  // y-координата левого верхнего угла окна 
		CW_USEDEFAULT,  // ширина окна 
		CW_USEDEFAULT,  // высота окна 
		NULL,     // дескриптор родительского окна 
		NULL,     // дескриптор меню окна 
		hInst,    // идентификатор приложения, создавшего окно 
		NULL);    // указатель на область данных приложения 

	/* 4. Отображение окна */

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);  // перерисовка окна 

	/* 5. Запуск цикла обработки сообщений  */

	// получение очередного сообщения из очереди сообщений 
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);  // трансляция сообщения 
		DispatchMessage(&lpMsg);  // диспетчеризация сообщений 
	}
	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			glb::x = 0;
			glb::y = 0;
			glb::t = 0;
			glb::horizontalMove = 0;
			glb::verticalMove = 0;
			MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
			SetTimer(hWnd, 1, glb::stepSpan, NULL);
		}
		else if (wParam == VK_ESCAPE)
			KillTimer(hWnd, 1);
		break;

	case WM_TIMER:
		glb::t++;
		WindowStep(hWnd);
		break;

	case WM_DESTROY:  		
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}

void WindowStep(HWND hWnd)
{
	HWND hWndScreen = GetDesktopWindow();
	RECT clientRect;
	GetClientRect(hWndScreen, &clientRect);	
	glb::screenX = clientRect.left;
	glb::screenY = clientRect.top;
	glb::screenWidth = clientRect.right;
	glb::screenHeight = clientRect.bottom;

	if (glb::y == 0  &&  glb::x < glb::screenWidth - glb::width)
	{
		glb::horizontalMove++;
		glb::x = glb::horizontalMove * glb::step;
		MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
	}

	if (glb::y < glb::screenHeight - glb::height && glb::x >= glb::screenWidth - glb::width)
	{
		glb::verticalMove++;
		glb::y = glb::verticalMove * glb::step;
		MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
	}

	if (glb::y >= glb::screenHeight - glb::height && glb::x > 0)
	{
		glb::horizontalMove--;
		glb::x = glb::horizontalMove * glb::step;
		MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
	}

	if (glb::y >= 0 && glb::x <= 0)
	{
		glb::verticalMove--;
		glb::y = glb::verticalMove * glb::step;
		MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
	}
}