//	Написати програму, в якій при натисненні довільної клавіши запускається тест,
//	який містить мінімум 3 питання.
//	Для запиту до користувача використати MessageBox.
//	Після проходження тесту на екрані власним шрифтом виводиться результат здачі тесту.

#include <windows.h> 
#include <tchar.h> 

namespace glb {
	INT answer1, answer2, answer3, result;
}

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение"); 

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
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);

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
		WS_OVERLAPPEDWINDOW,  // стиль окна 
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

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam,
	LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_KEYDOWN:
		glb::answer1 = MessageBox(hWnd, L"Do you know WinAPI theory?", L"Test of knowlage. Question number one.", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);
		glb::answer2 = MessageBox(hWnd, L"Can you code?", L"Test of knowlage. Question number two.", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);
		glb::answer3 = MessageBox(hWnd, L"Can you read a code?", L"Test of knowlage. Question number three", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);

		glb::result = glb::answer1 + glb::answer2 + glb::answer3;

		if (glb::result == 18)
			MessageBox(hWnd, L"Excellent! Keep moving", L"Test of knowlage. Your result.", MB_ICONEXCLAMATION);
		else if (glb::result == 19)
			MessageBox(hWnd, L"Good for you! Try to improve your skills!", L"Test of knowlage. Your result.", MB_ICONINFORMATION);
		else if (glb::result == 20)
			MessageBox(hWnd, L"Not bad. Try to improve your skills!", L"Test of knowlage. Your result.", MB_ICONINFORMATION);
		else if (glb::result == 21)
			MessageBox(hWnd, L"Sour, but don't be upset. See you next time ", L"Test of knowlage. Your result.", MB_ICONSTOP);

		break;

	case WM_DESTROY:  
		PostQuitMessage(0); 
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}