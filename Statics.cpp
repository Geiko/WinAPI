//	1.  ����������� ����������, ��������� �� ������ ����������� ����, �
//	���������� ��������� �����������������.
//
//	-  ������������ �������� ����� ������� ���� �� ����� �������
//	�, �� �������� ������, ���� �� ��� �����, � � ������ ����������
//	������  ��  ����������  �����������  �������������� (��� ��������, 
//	����  �����  ��  ���������  ����������  ���  �������� ��������������)
//	��������  �������, �������  ��������  ���� ���������� �����
//	(������� � ���� ������� ��������� �������� �� �����).
//
//	-  ����������� ������ �������� ���������� 10�10, � ��� ������� 
//	�������� �������� ���������� ������� �������� ������������ ������ 
//	������� ��������������� ��������������.
//
//	-  ��� ������ ������ ������� ���� ��� ������������ �������� � 
//	��������� ���� ������ ��������� ���������� � ������� (���������� �����
//	��������, ������ � ������, � ����� ���������� �������� ������������ 
//	������������� ����). � ������ ���� � ����� ������ ��������� ���������
//	���������, �� ������������ �������� �������� � ���������� 
//	���������� �������.
//
//	-  ���  �������  ������  �����  ������  ����  ���  ������������
//	�������� �� ������ ��������� � ����� (��� ����� ����� ��������������� 
//	�������� DestroyWindow, ������� � ��� ���������������� ������� 
//	��������). � ������ ���� � ����� ������ ���������  ��������� ���������, 
//	��  ������������  �������� �������� � ���������� ���������� �������.
//
//	���  ����������  ����������  �������������  ������������  ���������� STL.


#include <windows.h> 
#include "resource.h" 
#include <vector>

namespace glb {
	HWND  hStatic1, hWinPoint;
	HINSTANCE hInst;
	INT LEFT = 0, TOP = 0, WIDTH = 10, HEIGHT = 10, X, Y, minSize = 10, i = 0, xRight, yRight;
	TCHAR info[128], infoRight[128], agrigate[128];
	std::vector<HWND> myVector;
}

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL,	DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_LBUTTONDOWN:
		glb::LEFT = LOWORD(lParam);					
		glb::TOP = HIWORD(lParam);					
		return TRUE;

	case WM_LBUTTONUP:
		glb::X = LOWORD(lParam);					
		glb::Y = HIWORD(lParam);					

		if (glb::X < glb::LEFT)		{
			glb::WIDTH = glb::LEFT - glb::X;
			glb::LEFT = glb::X;
		}
		else{
			glb::WIDTH = glb::X - glb::LEFT;
		}
		if (glb::Y < glb::TOP)		{
			glb::HEIGHT = glb::TOP - glb::Y;
			glb::TOP = glb::Y;
		}
		else{
			glb::HEIGHT = glb::Y - glb::TOP;
		}
		if (glb::WIDTH < glb::minSize || glb::HEIGHT < glb::minSize){
			SetWindowText(hWnd, TEXT("Size of a static window cannot be less than 10x10 pixels!"));
			return TRUE;
		}
		else {
			glb::hStatic1 = CreateWindowEx(0, TEXT("STATIC"), 0, WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER |
				WS_EX_CLIENTEDGE, glb::LEFT, glb::TOP, glb::WIDTH, glb::HEIGHT, hWnd, 0, glb::hInst, 0);
			glb::i++;
			wsprintf(glb::info, TEXT("%d"), glb::i);
			SetWindowText(glb::hStatic1, glb::info);

			glb::myVector.push_back(glb::hStatic1);
			return TRUE;
		}

	case WM_RBUTTONDOWN:
		glb::xRight = LOWORD(lParam);
		glb::yRight = HIWORD(lParam);

		for (int j = glb::myVector.size() - 1; j >= 0; j--) {
			WINDOWPLACEMENT S;
			S.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(glb::myVector[j], &S);

			if (glb::xRight >= S.rcNormalPosition.left && glb::xRight <= S.rcNormalPosition.right &&
				glb::yRight >= S.rcNormalPosition.top && glb::yRight <= S.rcNormalPosition.bottom) {
				wsprintf(glb::infoRight, TEXT("Static number: %d,   X: %d, Y: %d,   Width: %d, Height: %d"),
					j + 1, S.rcNormalPosition.left, S.rcNormalPosition.top,
					S.rcNormalPosition.right - S.rcNormalPosition.left, 
					S.rcNormalPosition.bottom - S.rcNormalPosition.top);
				SetWindowText(hWnd, glb::infoRight);
				break;
			}
		}
		return TRUE;

	case WM_LBUTTONDBLCLK:
		POINT leftDblClick;
		leftDblClick.x = LOWORD(lParam);
		leftDblClick.y = HIWORD(lParam);
		glb::hWinPoint = ChildWindowFromPoint(hWnd, leftDblClick);
		if (glb::hWinPoint != NULL  &&  glb::hWinPoint != hWnd) {
				DestroyWindow(glb::hWinPoint);
				for (size_t j = 0; j < glb::myVector.size(); j++) {
					if (glb::hWinPoint == glb::myVector[j])
						glb::myVector.erase(glb::myVector.begin()+j);
				}
		}
		return TRUE;
	}
	return FALSE;
}