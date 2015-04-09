//	3. ��������  ����������, �����������  ���  �������  �����  ������
//	����  ��������  �����  �  ���������  ����  ������������  ����������
//	������������, �  ���  �������  ������  ������  ����  ��������
//	������ ������ �����, ������� �� ��� �������.

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
	// ������ ������� ���� ���������� �� ������ ������������ ������� 
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	// ���������� ����   
	ShowWindow(hDialog, nCmdShow);

	//��������� ���� ��������� ��������� 
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
	HWND hWindow = (HWND)lParam; // ���������� ���� ������ ���������� 
	TCHAR caption[MAX_PATH] = { 0 }, classname[100] = { 0 }, text[500] = { 0 };
	// �������� ����� ��������� �������� ��������� ���� 
	GetWindowText(hWnd, caption, 100);

	if (lstrcmp(caption, TEXT("����")) == 0)
	{
		SetWindowText(hWnd, TEXT("STOP"));	

		RECT clientRect;
		GetClientRect(hWnd, &clientRect);		//�-��� ����������� �������� ������
		glb::buttonX = clientRect.left;
		glb::buttonY = clientRect.top;
		glb::buttonWidth = clientRect.right;
		glb::buttonHeight = clientRect.bottom;

		MoveWindow(hWnd, glb::calcWidth - glb::buttonWidth, 100, glb::buttonWidth, glb::buttonHeight, 1);
		return FALSE;
	}
	return TRUE; // ���������� ������������ �������� ���� 
}


BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp)
{
	switch (mes)
	{
	case WM_CLOSE:
		// ��������� ����������� ������ 
		DestroyWindow(hWnd); // ��������� ���� 
		// ������������� ���� ��������� ��������� 
		PostQuitMessage(0);
		return TRUE;

	case WM_LBUTTONDOWN:
		wcscpy_s(glb::calcNewText, TEXT("It is not a calculator. It is non modal dialog window."));
		SetWindowText(hWnd, glb::calcNewText);
		break;

	case WM_RBUTTONDOWN:
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);		//�-��� ����������� �������� ����������� ����
		glb::calcWidth = clientRect.right;
		// �������� ������������ �������� ���� "������������"  
		EnumChildWindows(hWnd, EnumChildProc, (LPARAM)hWnd);
		break;
	}
	return FALSE;
}