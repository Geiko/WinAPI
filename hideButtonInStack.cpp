//	7. Написать  приложение, обладающее  следующей    функциональностью:
//
//	-  при  последовательном  нажатии  клавиши  <Enter>  дочерние
//	окна главного окна приложения «Калькулятор» минимизируются;
//
//	-  при последовательном нажатии клавиши <Esc> дочерние окна
//	восстанавливаются в обратном порядке, т.е.дочернее окно, которое
//	минимизировалось последним, первым будет восстановлено.

#include <windows.h> 
#include <tchar.h>
#include "resource.h" 
#include <time.h>
#include <stack>

namespace glb {
	TCHAR str[128];
	std::stack <HWND> stack1;
	std::stack <HWND> stack2;
	BOOL doneMin = 0;
}

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	MSG msg;
	// создаём главное окно приложения на основе немодального диалога 
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	ShowWindow(hDialog, nCmdShow);

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp)
{
	SetFocus(hWnd);
	EnumChildWindows(hWnd, EnumChildProc, (LPARAM)hWnd);
	switch (mes)
	{
	case  WM_KEYDOWN:
		if (wp == VK_RETURN)
		{
			if (glb::stack1.size() == 0) break;
			ShowWindow(glb::stack1.top(), SW_MINIMIZE);
			UpdateWindow(hWnd);
			glb::stack2.push( glb::stack1.top() );
			glb::stack1.pop();
		}

		else if (wp == VK_ESCAPE)
		{
			if (glb::stack2.size() <= 0) break;
			ShowWindow(glb::stack2.top(), SW_RESTORE);
			UpdateWindow(hWnd);
			glb::stack1.push(glb::stack2.top());
			glb::stack2.pop();
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
	HWND hWindow = (HWND)lParam;
	if (!IsIconic(hWnd))
		glb::stack1.push(hWnd);
	
	return TRUE;
}