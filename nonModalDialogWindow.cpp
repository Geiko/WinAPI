#include <windows.h> 
#include "resource.h" 

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine,	int nCmdShow)
{
	MSG msg;
	// создаём главное окно приложения на основе немодального диалога 
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	// Отображаем окно   
	ShowWindow(hDialog, nCmdShow);

	//Запускаем цикл обработки сообщений 
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp)
{

	switch (mes)
	{
	case WM_CLOSE:
		// закрываем немодальный диалог 
		DestroyWindow(hWnd); // разрушаем окно 
			// останавливаем цикл обработки сообщений 
			PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}