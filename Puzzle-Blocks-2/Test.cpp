//	1.  Модифицировать  интерфейс  приложения  «Пятнашки»  следующим образом : 

//		дополнить главное окно приложения строкой состояния, разделённой  на  две  секции.
//		В  первую  секцию  необходимо  выводить время продолжения игры, 
//		а во вторую секцию следует поместить индикатор процесса, 
//		который будет отображать процесс собирания «пятнашек» 
//		(процент попадания кнопок на свои места).



#include"PiatnashkyDlg.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	PiatnashkyDlg dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, PiatnashkyDlg::DlgProc);
}
