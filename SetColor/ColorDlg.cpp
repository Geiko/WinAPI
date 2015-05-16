#include "ColorDlg.h"


ColorDlg* ColorDlg::ptr = NULL;

ColorDlg::ColorDlg(void)
{
	ptr = this;
}

void ColorDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL ColorDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	HWND hOK = GetDlgItem(hwnd, IDOK);
	DestroyWindow(hOK);
	HWND hCancel = GetDlgItem(hwnd, IDCANCEL);
	DestroyWindow(hCancel);

	hProgress1 = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
		LEFT, TOP, WIDTH, HEIGHT, hwnd, NULL, NULL, NULL);

	hProgress11 = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
		LEFT11, TOP11, WIDTH11, HEIGHT11, hwnd, NULL, NULL, NULL);

	hProgress12 = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
		LEFT12, TOP12, WIDTH12, HEIGHT12, hwnd, NULL, NULL, NULL);

	hProgress13 = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
		LEFT13, TOP13, WIDTH13, HEIGHT13, hwnd, NULL, NULL, NULL);


	hSlider1 = CreateWindowEx(0, TRACKBAR_CLASS, NULL, WS_CHILD | WS_VISIBLE | TBS_NOTICKS | TBS_TOOLTIPS,
		LEFT1, TOP1, WIDTH1, HEIGHT1, hwnd, NULL, NULL, NULL);
	SendMessage(hSlider1, TBM_SETRANGE, TRUE, MAKELPARAM(0, 255));
	SendMessage(hSlider1, TBM_SETPOS, TRUE, red);

	hSlider2 = CreateWindowEx(0, TRACKBAR_CLASS, NULL, WS_CHILD | WS_VISIBLE | TBS_NOTICKS | TBS_TOOLTIPS,
		LEFT2, TOP2, WIDTH2, HEIGHT2, hwnd, NULL, NULL, NULL);
	SendMessage(hSlider2, TBM_SETRANGE, TRUE, MAKELPARAM(0, 255));
	SendMessage(hSlider2, TBM_SETPOS, TRUE, green);

	hSlider3 = CreateWindowEx(0, TRACKBAR_CLASS, NULL, WS_CHILD | WS_VISIBLE | TBS_NOTICKS | TBS_TOOLTIPS,
		LEFT3, TOP3, WIDTH3, HEIGHT3, hwnd, NULL, NULL, NULL);
	SendMessage(hSlider3, TBM_SETRANGE, TRUE, MAKELPARAM(0, 255));
	SendMessage(hSlider3, TBM_SETPOS, TRUE, blue);

	Tune(hwnd);
	return TRUE;
}

void ColorDlg::Cls_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
{
	red = SendMessage(hSlider1, TBM_GETPOS, NULL, NULL);
	green = SendMessage(hSlider2, TBM_GETPOS, NULL, NULL);
	blue = SendMessage(hSlider3, TBM_GETPOS, NULL, NULL);
	Tune(hwnd);
}

BOOL CALLBACK ColorDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_HSCROLL, ptr->Cls_OnHScroll);
	}
	return FALSE;
}
void ColorDlg::Tune(HWND hwnd)
{
	wsprintf(caption, TEXT("Red: %03d,    Green: %03d,    Blue: %03d"), red, green, blue);
	SetWindowText(hwnd, caption);
	SendMessage(hProgress1, PBM_SETBKCOLOR, 0, LPARAM(RGB(red, green, blue)));
	SendMessage(hProgress11, PBM_SETBKCOLOR, 0, LPARAM(RGB(red, 0, 0)));
	SendMessage(hProgress12, PBM_SETBKCOLOR, 0, LPARAM(RGB(0, green, 0)));
	SendMessage(hProgress13, PBM_SETBKCOLOR, 0, LPARAM(RGB(0, 0, blue)));
}