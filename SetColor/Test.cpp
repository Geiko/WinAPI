//	3.  Разработать приложение, позволяющее с помощью трёх ползунков
//		настраивать цвет фона индикатора.


#include"ColorDlg.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	ColorDlg dlg;

	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, ColorDlg::DlgProc);
}