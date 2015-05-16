#pragma once
#include"header.h"

class ColorDlg
{
private:
	INT LEFT = 300, TOP = 16, WIDTH = 160, HEIGHT = 256;

	INT LEFT11 = 1, TOP11 = 64, WIDTH11 = 30, HEIGHT11 = 30;
	INT LEFT12 = 1, TOP12 = 128, WIDTH12 = 30, HEIGHT12 = 30;
	INT LEFT13 = 1, TOP13 = 192, WIDTH13 = 30, HEIGHT13 = 30;

	INT LEFT1 = 32, TOP1 = 64, WIDTH1 = 256, HEIGHT1 = 32;
	INT LEFT2 = 32, TOP2 = 128, WIDTH2 = 256, HEIGHT2 = 32;
	INT LEFT3 = 32, TOP3 = 192, WIDTH3 = 256, HEIGHT3 = 32;

	INT red = 217, green = 127, blue = 41;
	HWND hProgress1, hProgress11, hProgress12, hProgress13, hSlider1, hSlider2, hSlider3;
	TCHAR caption[64];

	static ColorDlg *ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos);
	void Cls_OnClose(HWND hwnd);
	void Tune(HWND hwnd);

public:
	ColorDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);

};
