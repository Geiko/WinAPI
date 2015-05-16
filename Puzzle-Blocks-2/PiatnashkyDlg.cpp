#include "PiatnashkyDlg.h"


PiatnashkyDlg* PiatnashkyDlg::ptr = NULL;

PiatnashkyDlg::PiatnashkyDlg(void)
{
	ptr = this;
}

void PiatnashkyDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL PiatnashkyDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	SetWindowText(hwnd, TEXT("«Puzzle-Blocks»"));

	RECT clRect;
	GetClientRect(hwnd, &clRect);
	stoneSize = clRect.bottom / fildSize - 5;
	fildSizePcl = stoneSize * fildSize;

	CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"),
		TEXT(""), WS_CHILD | WS_VISIBLE,
		0, 0, fildSizePcl, fildSizePcl,
		hwnd, 0, hInst, 0);

	hUpdateSet = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("UPDATE SET"), WS_CHILD | WS_VISIBLE | BS_MULTILINE,
		fildSizePcl + 52, 32, 128, 128, hwnd, 0, hInst, 0);

	hStatusBar = CreateWindowEx(0, STATUSCLASSNAME, 0,
		WS_CHILD | WS_VISIBLE | SBT_TOOLTIPS | CCS_BOTTOM | SBARS_SIZEGRIP,
		0, 0, 0, 0, hwnd, HMENU(WM_USER), 0, 0);
	int parts[2] = { clRect.right/2, -1 };
	SendMessage(hStatusBar, SB_SETPARTS, 2, (LPARAM)parts);
	SendMessage(hStatusBar, SB_SETBKCOLOR, 0, (LPARAM)RGB(0, 255, 0));
	
	RECT r;
	SendMessage(hStatusBar, SB_GETRECT, 1, (LPARAM)&r);
	hProgressBar = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE,
		r.left + 3, r.top + 3, r.right - r.left, r.bottom - r.top,
		hStatusBar, NULL, NULL, NULL);
	SendMessage(hProgressBar, PBM_SETBKCOLOR, 0, LPARAM(RGB(0, 0, 255)));
	SendMessage(hProgressBar, PBM_SETBARCOLOR, 0, LPARAM(RGB(255, 255, 0)));

	HWND hOK = GetDlgItem(hwnd, IDOK);
	DestroyWindow(hOK);
	HWND hCancel = GetDlgItem(hwnd, IDCANCEL);
	DestroyWindow(hCancel);

	StartNewGame(hwnd);
	return TRUE;
}

void PiatnashkyDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HWND h = GetFocus();
	if (h == hUpdateSet)
	{
		PiatnashkyDlg::DestroyStones();
		PiatnashkyDlg::StartNewGame(hwnd);
		t = 0;
	}

	if (h != hUpdateSet)
	{
		TCHAR text[3];
		GetWindowText(h, text, 3);
		INT stone = _wtoi(text);

		if (stone > 0 && stone < fildSize * fildSize)
			PiatnashkyDlg::MoveStone(hwnd, h);
	}
}

void PiatnashkyDlg::Cls_OnTimer(HWND hwnd, UINT id)
{
	t++;
	sec = t % 60;
	min = (t - sec) / 60;
	wsprintf(timeCH, TEXT("Game duration:         %02d : %02d"), min, sec);
	SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)timeCH);
}

BOOL CALLBACK PiatnashkyDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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

VOID PiatnashkyDlg::StartNewGame(HWND hwnd)
{
	SetTimer(hwnd, 1, 1000, NULL);
	for (INT i = 1; i < fildSize * fildSize; ++i)
		numberVector.push_back(i);

	for (INT j = 0; j < fildSize; ++j)
	{
		for (INT i = 0; i < fildSize; ++i)
		{
			if (j == fildSize - 1 && i == fildSize - 1)
			{
				Blocks[j][i] = NULL;
				continue;
			}
			srand(time(NULL));
			stoneNumber = rand() % numberVector.size();
			_itow_s(numberVector[stoneNumber], stoneNum, 10);
			numberVector.erase(numberVector.begin() + stoneNumber);
			HWND hBlocks = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
				stoneNum, WS_CHILD | WS_VISIBLE,
				i * stoneSize, j * stoneSize,
				stoneSize, stoneSize, hwnd, 0, hInst, 0);
			Blocks[j][i] = hBlocks;
		}
	}	
	if (PiatnashkyDlg::CheckEnd(hwnd) == TRUE)
	{
		KillTimer(hwnd, 1);
	}
}

VOID PiatnashkyDlg::MoveStone(HWND hwnd, HWND h)
{
	INT x = -1, y = -1;

	PiatnashkyDlg::FindCoordinates(h, x, y);
	INT xClick = x;
	INT yClick = y;

	x = -1, y = -1;
	PiatnashkyDlg::FindCoordinates(NULL, x, y);
	INT xEmpty = x;
	INT yEmpty = y;


	if (xClick == xEmpty)
	{
		PiatnashkyDlg::yShift(h, xClick, yClick, yEmpty);
	}
	else if (yClick == yEmpty)
	{
		PiatnashkyDlg::xShift(h, xClick, yClick, xEmpty);
	}

	if (PiatnashkyDlg::CheckEnd(hwnd) == TRUE)
	{
		KillTimer(hwnd, 1);
	}
}


VOID PiatnashkyDlg::FindCoordinates(HWND h, INT &x, INT &y)
{
	for (INT j = 0; j < fildSize; ++j) {
		for (INT i = 0; i < fildSize; ++i) {
			if (Blocks[j][i] == h) {
				y = j;
				x = i;
				break;
			}
		}
	}
}

VOID PiatnashkyDlg::yShift(HWND h, INT xClick, INT yClick, INT yEmpty)
{
	INT loop = abs(yEmpty - yClick);
	for (INT s = 0; s < loop; ++s)
	{
		int sign = (yClick - yEmpty) / abs(yClick - yEmpty);

		MoveWindow(Blocks[yEmpty + sign][xClick], xClick * stoneSize,
			yEmpty * stoneSize, stoneSize, stoneSize, 1);

		HWND temp = Blocks[yEmpty][xClick];
		Blocks[yEmpty][xClick] = Blocks[yEmpty + sign][xClick];
		Blocks[yEmpty + sign][xClick] = temp;
		yEmpty = yEmpty + sign;
	}
}

VOID PiatnashkyDlg::xShift(HWND h, INT xClick, INT yClick, INT xEmpty)
{
	INT loop = abs(xEmpty - xClick);
	for (INT s = 0; s < loop; ++s)
	{
		int sign = (xClick - xEmpty) / abs(xClick - xEmpty);

		MoveWindow(Blocks[yClick][xEmpty + sign], xEmpty * stoneSize,
			yClick * stoneSize, stoneSize, stoneSize, 1);

		HWND temp = Blocks[yClick][xEmpty];
		Blocks[yClick][xEmpty] = Blocks[yClick][xEmpty + sign];
		Blocks[yClick][xEmpty + sign] = temp;
		xEmpty = xEmpty + sign;
	}
}

VOID PiatnashkyDlg::DestroyStones()
{
	for (INT j = 0; j < fildSize; ++j) {
		for (INT i = 0; i < fildSize; ++i) {
			if (!Blocks[j][i]) continue;
			DestroyWindow(Blocks[j][i]);
		}
	}
}

BOOL PiatnashkyDlg::CheckEnd(HWND hwnd)
{
	TCHAR text[3];
	INT order = 0, right = 0;
	BOOL result = TRUE;
	for (INT j = 0; j < fildSize; ++j) {
		for (INT i = 0; i < fildSize; ++i) {
			order++;
			if (Blocks[j][i] == NULL && j != fildSize && i != fildSize)
			{
				result = FALSE;
				continue;
			}
			else if (Blocks[j][i] == NULL && j == fildSize && i == fildSize)
			{
				right++;
				continue;
			}

			GetWindowText(Blocks[j][i], text, 3);
			INT stone = _wtoi(text);

			if (stone != order) result = FALSE;
			else right++;
		}
	}
	FLOAT perCent = right * 100 / fildSize / fildSize;
	SendMessage(hProgressBar, PBM_SETPOS, (INT)perCent, 0);
	return result;
}