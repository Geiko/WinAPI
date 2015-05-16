#include "W62Dlg.h"


W62Dlg* W62Dlg::ptr = NULL;

W62Dlg::W62Dlg(void)
{
	ptr = this;
}

void W62Dlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL W62Dlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	SetWindowText(hwnd, TEXT("00 : 00    Please, click buttons in increasing order."));

	HWND hOK = GetDlgItem(hwnd, IDOK);
	DestroyWindow(hOK);
	HWND hCancel = GetDlgItem(hwnd, IDCANCEL);
	DestroyWindow(hCancel);

	RECT clRect;
	GetClientRect(hwnd, &clRect);
	stoneSize = clRect.bottom / fildSize - 5;
	fildSizePcl = stoneSize * fildSize;

	CreateStonse(hwnd);
	CreateStartButton(hwnd);
	CreateStatusProgress(hwnd);
	CreateCounter(hwnd);
	CreateList(hwnd);

	return TRUE;
}

void W62Dlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HWND h = GetFocus();
	if (h == hUpdateSet)
	{
		W62Dlg::StartNewGame(hwnd);
		t = 0;
	}

	if (h != hUpdateSet)
	{
		TCHAR text[5];
		GetWindowText(h, text, 4);
		INT stone = _wtoi(text);

		if (stone >= 0 && stone <= numberMax)
		{
			W62Dlg::CheckOrder(hwnd, h, stone);
		}
	}
}

void W62Dlg::Cls_OnTimer(HWND hwnd, UINT id)
{
	t++;
	sec = t % 60;
	min = (t - sec) / 60;
	wsprintf(timeCH, TEXT("%02d : %02d    Please, click buttons in increasing order."), min, sec);
	SetWindowText(hwnd, timeCH);

	if (nTime == t)
	{
		KillTimer(hwnd, 1);
		for (INT j = 0; j < fildSize; ++j)
		{
			for (INT i = 0; i < fildSize; ++i)
			{
				EnableWindow(Blocks[j][i], 0);
			}
		}
	}
	FLOAT perCent = t * 100 / nTime;
	SendMessage(hProgressBar, PBM_SETPOS, (INT)perCent, 0);
}

BOOL CALLBACK W62Dlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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


void W62Dlg::CreateStonse(HWND hwnd)
{
	srand(time(NULL));
	for (INT j = 0; j < fildSize; ++j)
	{
		for (INT i = 0; i < fildSize; ++i)
		{
			stoneNumber = rand() % (numberMax + 1);
			numberList.push_back(stoneNumber);
			_itow_s(stoneNumber, stoneNum, 10);

			Blocks[j][i] = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
				stoneNum, WS_CHILD | WS_VISIBLE,
				i * stoneSize, j * stoneSize,
				stoneSize, stoneSize, hwnd, 0, hInst, 0);
			EnableWindow(Blocks[j][i], 0);
		}
	}
}

void W62Dlg::CreateStartButton(HWND hwnd)
{
	hUpdateSet = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("START GAME"), WS_CHILD | WS_VISIBLE | BS_MULTILINE,
		fildSizePcl + 32, 32, 64, 64, hwnd, 0, hInst, 0);
}

void W62Dlg::CreateCounter(HWND hwnd)
{
	hSpin = GetDlgItem(hwnd, IDC_SPIN1);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
	SendMessage(hSpin, UDM_SETRANGE32, 10, 100);
	SendMessage(hSpin, UDM_SETBUDDY, WPARAM(hEdit2), 0);

	TCHAR duration[4];
	_itow_s(nTime, duration, 10);
	SetWindowText(hEdit2, duration);
}

void W62Dlg::CreateStatusProgress(HWND hwnd)
{
	hStatusBar = CreateWindowEx(0, STATUSCLASSNAME, 0,
		WS_CHILD | WS_VISIBLE | SBT_TOOLTIPS | CCS_BOTTOM | SBARS_SIZEGRIP,
		0, 0, 0, 0, hwnd, HMENU(WM_USER), 0, 0);
	RECT r;
	SendMessage(hStatusBar, SB_GETRECT, 0, (LPARAM)&r);
	hProgressBar = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE,
		r.left + 3, r.top + 3, r.right - r.left, r.bottom - r.top,
		hStatusBar, NULL, NULL, NULL);
	SendMessage(hProgressBar, PBM_SETBKCOLOR, 0, LPARAM(RGB(0, 0, 255)));
	SendMessage(hProgressBar, PBM_SETBARCOLOR, 0, LPARAM(RGB(255, 255, 0)));

}

void W62Dlg::CreateList(HWND hwnd)
{
	hList = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("LISTBOX"), 0,
		WS_CHILD | WS_VISIBLE | LBS_NOSEL | LBS_STANDARD,
		fildSizePcl + 128, 32, 64, 220, hwnd, NULL, NULL, NULL);
}

VOID W62Dlg::StartNewGame(HWND hwnd)
{
	SendMessage(hList, LB_RESETCONTENT, 0, 0);
	SetTimer(hwnd, 1, 1000, NULL);

	numberList.clear();

	srand(time(NULL));
	for (INT j = 0; j < fildSize; ++j)
	{
		for (INT i = 0; i < fildSize; ++i)
		{
			stoneNumber = rand() % (numberMax + 1);
			numberList.push_back(stoneNumber);
			_itow_s(stoneNumber, stoneNum, 10);
			SetWindowText(Blocks[j][i], stoneNum);
			EnableWindow(Blocks[j][i], 1);
		}
	}
	numberList.list::sort();
	nTime = SendMessage(hSpin, UDM_GETPOS32, 0, 0);
}

BOOL W62Dlg::CheckOrder(HWND hwnd, HWND h, INT stone)
{
	if (stone == *numberList.begin())
	{
		numberList.pop_front();

		TCHAR* strNumber = new TCHAR[4];
		wsprintf(strNumber, TEXT("%03d"), stone);
		SendMessage(hList, LB_ADDSTRING, 0, LPARAM(strNumber));
		delete[] strNumber;

		EnableWindow(h, 0);

		if (numberList.size() == 0)
		{
			KillTimer(hwnd, 1);
		}
		return TRUE;
	}
	else return FALSE;
}