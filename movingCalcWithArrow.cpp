//	4. Написать  приложение, обладающее  следующей  функциональностью:
//
//	-  при нажатии кнопки <Enter> окно приложения позиционируется
//		в левый верхний угол экрана с размерами(300Х300);
//
//	-  с помощью клавиш управления курсором осуществляется перемещение окна.

#include <windows.h> 
#include <tchar.h> 

namespace glb {
	INT i = 0, j = 0, step = 21, x = 0, y = 0, width = 300, height = 300;
}

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
	case  WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			glb::i = glb::j = glb::x = glb::y = 0;
			MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
		}
		if (wParam == VK_RIGHT)
		{
			glb::i++;
			glb::x = glb::i * glb::step;
			MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
		}
		if (wParam == VK_LEFT)
		{
			glb::i--;
			glb::x = glb::i * glb::step;
			MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
		}
		if (wParam == VK_DOWN)
		{
			glb::j++;
			glb::y = glb::j * glb::step;
			MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
		}
		if (wParam == VK_UP)
		{
			glb::j--;
			glb::y = glb::j * glb::step;
			MoveWindow(hWnd, glb::x, glb::y, glb::width, glb::height, 1);
		}
		break;
	case WM_DESTROY:  
		PostQuitMessage(0);  
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}