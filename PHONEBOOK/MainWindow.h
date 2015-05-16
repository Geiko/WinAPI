#pragma once
#include "Splash.h"

class Abonent;
class PhoneBook;
namespace UI {
	class MainWindow
	{
		RECT clientRectM;
		HWND hButtonAdd, hEdit, hCombo, hButtonDelete, hButtonChange;
		INT left, top, width, height, gap = 8;

		void SetButtons(HWND hwnd);
		void SetAbonentList(HWND hwnd);
		void SetAbonentData(HWND hwnd);
		void SetAbonentDataList(HWND hwnd);

		PhoneBook* myPhoneBook;


		static MainWindow* ptr;
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void Cls_OnClose(HWND hwnd);

	public:
		MainWindow(PhoneBook* myPhoneBook);
		static BOOL CALLBACK dlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	};
}