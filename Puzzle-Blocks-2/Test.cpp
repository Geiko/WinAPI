//	1.  ��������������  ���������  ����������  ���������  ��������� ������� : 

//		��������� ������� ���� ���������� ������� ���������, ����������  ��  ���  ������.
//		�  ������  ������  ����������  �������� ����� ����������� ����, 
//		� �� ������ ������ ������� ��������� ��������� ��������, 
//		������� ����� ���������� ������� ��������� ��������� 
//		(������� ��������� ������ �� ���� �����).



#include"PiatnashkyDlg.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	PiatnashkyDlg dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, PiatnashkyDlg::DlgProc);
}
