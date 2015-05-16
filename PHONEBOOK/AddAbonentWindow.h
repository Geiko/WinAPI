#pragma once
#include "Splash.h"

class Abonent;
class Connection;
class PhoneBook;
namespace UI {
	class AddAbonentWindow
	{
	private:
		RECT clientRect;
		INT leftAbWnd = 0, topAbWnd = 0, widthAbWnd = 440, heightAbWnd = 670;
		INT leftAb, topAb, widthAb, heightAb, gap = 8;
		HWND hButtonAdd, hList, hButtonDelete, hButtonChange;
		HWND hOK, hCancel, hEditName, hRadio1, hRadio2, hRadio3, hCombo1, hCombo2, hCombo3, hEditComment;
		HWND hListPhone, hComboTypePhone, hEditPhone, hEditCommentPhone, hButtonAddConnect, hButtonDeleteConnect;

		std::vector<HWND> genderVector;
		std::vector<Connection>tempPhoneRepository;

		PhoneBook* myPhoneBook;

		void SetOkCancel(HWND hwnd);
		void SetName(HWND hwnd);
		void SetGender(HWND hwnd);
		void SetBirthDay(HWND hwnd);
		void SetComment(HWND hwnd);
		void SetNumberPhone(HWND hwnd);
		void SetTypePhone(HWND hwnd);
		void SetCommentPhone(HWND hwnd);
		void SetInputButton(HWND hwnd);
		void SetDeleteButton(HWND hwnd);
		
		void SetRadio(HWND h);
		void SetAbonentGender(Abonent& abonent);
		void SetAbonentBirthday(Abonent& abonent);
		void SetAbonentComment(Abonent& abonent);
		Connection SetRecordToPhoneList(TCHAR* phoneRecord);

		static AddAbonentWindow* ptr;
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void Cls_OnClose(HWND hwnd);

	public:
		AddAbonentWindow(PhoneBook* myPhoneBook);
		static BOOL CALLBACK dlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	};
}