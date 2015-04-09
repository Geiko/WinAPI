//	Написать  приложение, обладающее  следующей  функциональностью:
//
//	-  после нажатия клавиши <Enter> через каждую секунду(или
//	иной  промежуток  времени)  «прячется»  одна  из  кнопок
//	«Калькулятора», выбранная случайным образом;
//
//	-  после нажатия клавиши <Esc> данный процесс останавливается.

#include <windows.h> 
#include <tchar.h>
#include "resource.h" 
#include <time.h>
#include <vector>

namespace glb {
	TCHAR str[128];
	char numberStr[5] = "";
	UINT t = 0, Random;
	std::vector <HWND> myvector;
}

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	MSG msg;
	// создаём главное окно приложения на основе немодального диалога 
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	// Отображаем окно   
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



	switch (mes)
	{
	case  WM_KEYDOWN:
		if (wp == VK_RETURN)
			SetTimer(hWnd, 1, 1000, NULL);		
		else if (wp == VK_ESCAPE)
			KillTimer(hWnd, 1);
		break;

	case WM_TIMER:
		glb::t++;
		wsprintf(glb::str, TEXT("%03d"), glb::t);
		SetWindowText(hWnd, glb::str);

		EnumChildWindows(hWnd, EnumChildProc, (LPARAM)hWnd);
		if (glb::myvector.size() <= 0)
		{
			KillTimer(hWnd, 1);
			break;
		}
		srand(time(NULL));
		glb::Random = rand() % glb::myvector.size();
		ShowWindow(glb::myvector[glb::Random], SW_HIDE);
		glb::myvector.clear();
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
	if (IsWindowVisible(hWnd) == 0)
		return TRUE;
	glb::myvector.push_back(hWnd);
	return TRUE; 
}