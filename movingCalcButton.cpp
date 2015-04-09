//	3. Ќаписать  приложение, позвол€ющее  при  нажатии  левой  кнопки
//	мыши  изменить  текст  в  заголовке  окна  стандартного  приложени€
//	Ђ алькул€торї, а  при  нажатии  правой  кнопки  мыши  сместить
//	вправо кнопку Ђпускї, изменив на ней надпись.

#include <windows.h> 
#include <tchar.h>
#include "resource.h" 

namespace glb {
	TCHAR calcNewText[128];
	INT calcWidth, buttonX, buttonY, buttonWidth, buttonHeight;
}

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine,	int nCmdShow)
{
	MSG msg;
	// создаЄм главное окно приложени€ на основе немодального диалога 
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	// ќтображаем окно   
	ShowWindow(hDialog, nCmdShow);

	//«апускаем цикл обработки сообщений 
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
	HWND hWindow = (HWND)lParam; // дескриптор окна нашего приложени€ 
	TCHAR caption[MAX_PATH] = { 0 }, classname[100] = { 0 }, text[500] = { 0 };
	// получаем текст заголовка текущего дочернего окна 
	GetWindowText(hWnd, caption, 100);

	if (lstrcmp(caption, TEXT("ѕуск")) == 0)
	{
		SetWindowText(hWnd, TEXT("STOP"));	

		RECT clientRect;
		GetClientRect(hWnd, &clientRect);		//ф-ци€ определени€ размеров кнопки
		glb::buttonX = clientRect.left;
		glb::buttonY = clientRect.top;
		glb::buttonWidth = clientRect.right;
		glb::buttonHeight = clientRect.bottom;

		MoveWindow(hWnd, glb::calcWidth - glb::buttonWidth, 100, glb::buttonWidth, glb::buttonHeight, 1);
		return FALSE;
	}
	return TRUE; // продолжаем перечисление дочерних окон 
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

	case WM_LBUTTONDOWN:
		wcscpy_s(glb::calcNewText, TEXT("It is not a calculator. It is non modal dialog window."));
		SetWindowText(hWnd, glb::calcNewText);
		break;

	case WM_RBUTTONDOWN:
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);		//ф-ци€ определени€ размеров клиентского окна
		glb::calcWidth = clientRect.right;
		// начинаем перечисление дочерних окон " алькул€тора"  
		EnumChildWindows(hWnd, EnumChildProc, (LPARAM)hWnd);
		break;
	}
	return FALSE;
}