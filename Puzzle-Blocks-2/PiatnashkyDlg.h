#pragma once
#include"header.h"

class PiatnashkyDlg
{
private:
	TCHAR stoneNum[3], timeCH[100];
	static CONST UINT fildSize = 4;
	INT stoneSize, fildSizePcl, stoneNumber, k = 0, t = 0, sec, min;
	std::vector<INT>numberVector;
	HWND hUpdateSet, hTime, hStatusBar, hProgressBar;
	HWND Blocks[fildSize][fildSize];
	HINSTANCE hInst;

	static PiatnashkyDlg *ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	void Cls_OnTimer(HWND hwnd, UINT id);

	VOID StartNewGame(HWND);
	VOID MoveStone(HWND, HWND);
	VOID FindCoordinates(HWND h, INT &x, INT &y);
	VOID yShift(HWND, INT, INT, INT);
	VOID xShift(HWND, INT, INT, INT);
	VOID DestroyStones();
	BOOL CheckEnd(HWND hwnd);

public:
	PiatnashkyDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);

};
