#pragma once
#include "Header.h"
#include "MainWindow.h"
#include "AddAbonentWindow.h"
#include "PhoneBook.h"
#include "Abonent.h"
#include "Connection.h"

namespace UI {
	class Splash
	{
		INT t;
		HWND hSplash, hProgress1, hProgress2, hDialog, hButton;

		static Splash* ptr;
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void Cls_OnTimer(HWND hwnd, UINT id);
		void Cls_OnClose(HWND hwnd);
	public:
		Splash(void);
		static BOOL CALLBACK dlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	};
}