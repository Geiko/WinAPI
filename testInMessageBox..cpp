//	�������� ��������, � ��� ��� ��������� ������� ������ ����������� ����,
//	���� ������ ����� 3 �������.
//	��� ������ �� ����������� ����������� MessageBox.
//	ϳ��� ����������� ����� �� ����� ������� ������� ���������� ��������� ����� �����.

#include <windows.h> 
#include <tchar.h> 

namespace glb {
	INT answer1, answer2, answer3, result;
}

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("��������� ����������"); 

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine,	int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	/* 1. ����������� ������ ����  */

	wcl.cbSize = sizeof(wcl);  // ������ ��������� WNDCLASSEX  
	// ������������ �� ����, ���� ������ ������ �� �����������  
	// ��� �� ��������� 
	wcl.style = CS_HREDRAW | CS_VREDRAW; // CS(Class Style) - ����� ������ ���� 
	wcl.lpfnWndProc = WindowProc; // ����� ������� ��������� 
	wcl.cbClsExtra = 0;  // ������������ Windows  
	wcl.cbWndExtra = 0;   // ������������ Windows  
	wcl.hInstance = hInst;  // ���������� ������� ���������� 

	// �������� ����������� ������ 
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	// �������� ������������ ������� 
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);

	// ���������� ���� ����� ������     
	wcl.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wcl.lpszMenuName = NULL;  //���������� �� �������� ���� 
	wcl.lpszClassName = szClassWindow;  //��� ������ ���� 
	wcl.hIconSm = NULL; // ���������� ��������� ������ 

	/*  2. ����������� ������ ����  */

	if (!RegisterClassEx(&wcl))
		return 0; // ��� ��������� ����������� - ����� 

	/*  3. �������� ����  */

	// ��������� ���� �  ���������� hWnd ������������� ���������� ���� 
	hWnd = CreateWindowEx(
		0,    // ����������� ����� ���� 
		szClassWindow,  // ��� ������ ���� 
		TEXT("My first window."), // ��������� ���� 
		WS_OVERLAPPEDWINDOW,  // ����� ���� 
		/* ���������, �����, ����������� ������ �������, ��������� ����,
		������ ������������ � ���������� ����  */
		CW_USEDEFAULT,  // �-���������� ������ �������� ���� ���� 
		CW_USEDEFAULT,  // y-���������� ������ �������� ���� ���� 
		CW_USEDEFAULT,  // ������ ���� 
		CW_USEDEFAULT,  // ������ ���� 
		NULL,     // ���������� ������������� ���� 
		NULL,     // ���������� ���� ���� 
		hInst,    // ������������� ����������, ���������� ���� 
		NULL);    // ��������� �� ������� ������ ���������� 

	/* 4. ����������� ���� */

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);  // ����������� ���� 

	/* 5. ������ ����� ��������� ���������  */

	// ��������� ���������� ��������� �� ������� ��������� 
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);  // ���������� ��������� 
		DispatchMessage(&lpMsg);  // ��������������� ��������� 
	}
	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam,
	LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_KEYDOWN:
		glb::answer1 = MessageBox(hWnd, L"Do you know WinAPI theory?", L"Test of knowlage. Question number one.", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);
		glb::answer2 = MessageBox(hWnd, L"Can you code?", L"Test of knowlage. Question number two.", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);
		glb::answer3 = MessageBox(hWnd, L"Can you read a code?", L"Test of knowlage. Question number three", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);

		glb::result = glb::answer1 + glb::answer2 + glb::answer3;

		if (glb::result == 18)
			MessageBox(hWnd, L"Excellent! Keep moving", L"Test of knowlage. Your result.", MB_ICONEXCLAMATION);
		else if (glb::result == 19)
			MessageBox(hWnd, L"Good for you! Try to improve your skills!", L"Test of knowlage. Your result.", MB_ICONINFORMATION);
		else if (glb::result == 20)
			MessageBox(hWnd, L"Not bad. Try to improve your skills!", L"Test of knowlage. Your result.", MB_ICONINFORMATION);
		else if (glb::result == 21)
			MessageBox(hWnd, L"Sour, but don't be upset. See you next time ", L"Test of knowlage. Your result.", MB_ICONSTOP);

		break;

	case WM_DESTROY:  
		PostQuitMessage(0); 
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}