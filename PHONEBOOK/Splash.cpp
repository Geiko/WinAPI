#pragma once
#include"Splash.h"

UI::Splash* UI::Splash::ptr = NULL;

UI::Splash::Splash(void)
{
	ptr = this;
}

void UI::Splash::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL UI::Splash::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	using namespace UI;
	srand(time(0));
	hDialog = hwnd;

	HWND hOK = GetDlgItem(hwnd, IDOK);
	DestroyWindow(hOK);
	HWND hCancel = GetDlgItem(hwnd, IDCANCEL);
	DestroyWindow(hCancel);

	hButton = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Click me to load"), WS_CHILD | WS_VISIBLE | BS_MULTILINE,
		188, 32, 80, 80, hwnd, 0, 0, 0);

	hProgress1 = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
		77, 180, 300, 32, hDialog, NULL, NULL, NULL);
	SendMessage(hProgress1, PBM_SETRANGE, 0, MAKELPARAM(0, 60));  
	SendMessage(hProgress1, PBM_SETSTEP, 1, 0);  
	SendMessage(hProgress1, PBM_SETPOS, 0, 0); 
	SendMessage(hProgress1, PBM_SETBKCOLOR, 0, LPARAM(RGB(0, 0, 255))); 
	SendMessage(hProgress1, PBM_SETBARCOLOR, 0, LPARAM(RGB(255, 0, 0)));

	hProgress2 = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE,
		77, 240, 300, 16, hDialog, NULL, NULL, NULL);
	SendMessage(hProgress2, PBM_SETRANGE, 0, MAKELPARAM(0, 60));
	SendMessage(hProgress2, PBM_SETSTEP, 1, 0);
	SendMessage(hProgress2, PBM_SETPOS, 0, 0);
	SendMessage(hProgress2, PBM_SETBKCOLOR, 0, LPARAM(RGB(0, 255, 0)));
	SendMessage(hProgress2, PBM_SETBARCOLOR, 0, LPARAM(RGB(255, 255, 255)));
	return TRUE;
}

void UI::Splash::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HWND h = GetFocus();
	if (h == hButton)
		SetTimer(hwnd, 1, 100, 0);
}

void UI::Splash::Cls_OnTimer(HWND hwnd, UINT id)
{
	t++;
	if (t == 60)
	{
		KillTimer(hwnd, 1);
		SendMessage(hwnd, WM_CLOSE, 0, 0);
		DialogBox(0, MAKEINTRESOURCE(IDD_SPLASH), NULL, UI::MainWindow::dlgProc);
	}
	SendMessage(hProgress1, PBM_STEPIT, 0, 0);
	int n = rand() % 60;
	SendMessage(hProgress2, PBM_SETPOS, WPARAM(n), 0);	
}
	
BOOL CALLBACK UI::Splash::dlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_TIMER, ptr->Cls_OnTimer);
	}
	return FALSE;
}