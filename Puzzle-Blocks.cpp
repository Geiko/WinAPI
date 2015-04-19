//	4. Написать игру «Пятнашки», учитывая следующие требования :
//
//	-  предусмотреть  автоматическую  перестановку  «пятнашек»  в  начале новой игры;
//
//	-  выводить время, за которое пользователь окончил игру (собрал «пятнашки»)
//
//	-  предусмотреть возможность начать новую игру.

#include<Windows.h>
#include"resource.h"
#include<time.h>
#include<vector>

namespace glb {
	TCHAR stoneNum[3], time[7];
	CONST UINT fildSize = 4;
	INT stoneSize, fildSizePcl, stoneNumber, k = 0, t = 0, sec, min;
	HINSTANCE hInst;
	std::vector<INT>numberVector;
	HWND hUpdateSet, hResult, hTime;
	HWND Blocks[fildSize][fildSize];
}

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
VOID StartNewGame(HWND);
VOID MoveStone(HWND, HWND);
VOID FindCoordinates(HWND h, INT &x, INT &y);
VOID yShift(HWND, INT, INT, INT);
VOID xShift(HWND, INT, INT, INT);
VOID DestroyStones(); 
BOOL CheckEnd(); 

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, INT nCmdShow)
{
	glb::hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT mes, WPARAM wparam, LPARAM lparam){
	switch (mes)
	{
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;

	case WM_INITDIALOG:
		SetWindowText(hwnd, TEXT("«Puzzle-Blocks»"));

		RECT clRect;
		GetClientRect(hwnd, &clRect);
		glb::stoneSize = clRect.bottom / glb::fildSize;
		glb::fildSizePcl = glb::stoneSize * glb::fildSize;

		CreateWindowEx (WS_EX_CLIENTEDGE, TEXT("STATIC"),
			TEXT(""), WS_CHILD | WS_VISIBLE,
			0, 0, glb::fildSizePcl, glb::fildSizePcl, 
			hwnd, 0, glb::hInst, 0);
		
		glb::hUpdateSet = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
			TEXT("UPDATE SET"), WS_CHILD | WS_VISIBLE | BS_MULTILINE,
			glb::fildSizePcl + 32, 32, 128, 32, hwnd, 0, glb::hInst, 0);	

		glb::hResult = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"),
			TEXT(""), WS_CHILD | WS_VISIBLE | BS_MULTILINE,
			glb::fildSizePcl + 10, 70, 160, 50, hwnd, 0, glb::hInst, 0);

		glb::hTime = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"),
			TEXT(""), WS_CHILD | WS_VISIBLE | BS_MULTILINE,
			glb::fildSizePcl + 60, 200, 70, 20, hwnd, 0, glb::hInst, 0);

		StartNewGame(hwnd);
		return TRUE;

	case WM_TIMER:
		glb::t++;
		glb::sec = glb::t % 60;
		glb::min = (glb::t - glb::sec) / 60;
		wsprintf(glb::time, TEXT("    %02d:%02d"), glb::min, glb::sec);
		SetWindowText(glb::hTime, glb::time);
		return TRUE;

	case WM_COMMAND:
			HWND h = GetFocus();
			if (h == glb::hUpdateSet)
			{
				DestroyStones();
				StartNewGame(hwnd);
				glb::t = 0;
			}

			if (h != glb::hUpdateSet)
			{
				TCHAR text[3];
				GetWindowText(h, text, 3);
				INT stone = _wtoi(text);

				if (stone > 0 && stone < glb::fildSize * glb::fildSize)
					MoveStone(hwnd, h);
			}
		return TRUE;
	}
	return FALSE;
}

VOID StartNewGame(HWND hwnd)
{
	SetTimer(hwnd, 1, 1000, NULL);
	for (INT i = 1; i < glb::fildSize * glb::fildSize; ++i)
		glb::numberVector.push_back(i);

	for (INT j = 0; j < glb::fildSize; ++j)
	{
		for (INT i = 0; i < glb::fildSize; ++i)
		{
			if (j == glb::fildSize - 1 && i == glb::fildSize - 1)
			{
				glb::Blocks[j][i] = NULL;
				continue;
			}
			srand(time(NULL));
			glb::stoneNumber = rand() % glb::numberVector.size();
			_itow_s(glb::numberVector[glb::stoneNumber], glb::stoneNum, 10);
			glb::numberVector.erase(glb::numberVector.begin() + glb::stoneNumber);
			HWND hBlocks = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
				glb::stoneNum, WS_CHILD | WS_VISIBLE,
				i * glb::stoneSize, j * glb::stoneSize,
				glb::stoneSize, glb::stoneSize, hwnd, 0, glb::hInst, 0);
			glb::Blocks[j][i] = hBlocks;
		}
	}
}

VOID MoveStone(HWND hwnd, HWND h)
{
	INT x = -1, y = -1;
	FindCoordinates(h, x, y);	
	INT xClick = x;
	INT yClick = y;

	x = -1, y = -1;
	FindCoordinates(NULL, x, y);
	INT xEmpty = x;
	INT yEmpty = y;

	if (xClick == xEmpty)
	{
		yShift(h, xClick, yClick, yEmpty);
	}
	else if(yClick == yEmpty)
	{
		xShift(h, xClick, yClick, xEmpty);
	}
	else SetWindowText(glb::hResult, TEXT(" This stone can't be moved"));

	if (CheckEnd() == TRUE)
	{
		KillTimer(hwnd, 1);
		SetWindowText(glb::hResult, TEXT(" Congratulations!!! You have won!"));
	}
}


VOID FindCoordinates(HWND h, INT &x, INT &y)
{
	for (INT j = 0; j < glb::fildSize; ++j) {
		for (INT i = 0; i < glb::fildSize; ++i) {
			if (glb::Blocks[j][i] == h) {
				y = j;
				x = i;
				break;
			}
		}
	}
}

VOID yShift(HWND h, INT xClick, INT yClick, INT yEmpty)
{
		INT loop = abs(yEmpty - yClick);
		for (INT s = 0; s < loop; ++s)
		{
			int sign = (yClick - yEmpty) / abs(yClick - yEmpty);

			BOOL g = MoveWindow(glb::Blocks[yEmpty + sign][xClick], xClick * glb::stoneSize,
				yEmpty * glb::stoneSize, glb::stoneSize, glb::stoneSize, 1);

			HWND temp = glb::Blocks[yEmpty][xClick];
			glb::Blocks[yEmpty][xClick] = glb::Blocks[yEmpty + sign][xClick];
			glb::Blocks[yEmpty + sign][xClick] = temp;
			yEmpty = yEmpty + sign;
			if (g != 0)
				SetWindowText(glb::hResult, TEXT(" OK"));
			else
				SetWindowText(glb::hResult, TEXT(" Huston"));
		}
}

VOID xShift(HWND h, INT xClick, INT yClick, INT xEmpty)
{
	INT loop = abs(xEmpty - xClick);
	for (INT s = 0; s < loop; ++s)
	{
		int sign = (xClick - xEmpty) / abs(xClick - xEmpty);

		BOOL g = MoveWindow(glb::Blocks[yClick][xEmpty + sign], xEmpty * glb::stoneSize,
			yClick * glb::stoneSize, glb::stoneSize, glb::stoneSize, 1);

		HWND temp = glb::Blocks[yClick][xEmpty];
		glb::Blocks[yClick][xEmpty] = glb::Blocks[yClick][xEmpty + sign];
		glb::Blocks[yClick][xEmpty + sign] = temp;
		xEmpty = xEmpty + sign;
		if (g != 0)
			SetWindowText(glb::hResult, TEXT(" OK"));
		else
			SetWindowText(glb::hResult, TEXT(" Huston"));
	}
}

VOID DestroyStones()
{
	for (INT j = 0; j < glb::fildSize; ++j) {
		for (INT i = 0; i < glb::fildSize; ++i) {
			if (!glb::Blocks[j][i]) continue;
			DestroyWindow(glb::Blocks[j][i]);				
		}
	}
}

BOOL CheckEnd()
{
	INT check = 0;
	for (INT j = 0; j < glb::fildSize; ++j) {
		for (INT i = 0; i < glb::fildSize; ++i) {
			check++;
			if (check == glb::fildSize * glb::fildSize) return TRUE;
			TCHAR text[3];
			GetWindowText(glb::Blocks[j][i], text, 3);
			INT stone = _wtoi(text);
			if (stone != check) return FALSE;
		}
	}
	return TRUE;
}