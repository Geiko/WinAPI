#include "ChangeDataWindow.h"

//UI::ChangeDataWindow* UI::ChangeDataWindow::ptr = NULL;

//UI::ChangeDataWindow::ChangeDataWindow(PhoneBook* myPhoneBook)
//{
//	this->myPhoneBook = myPhoneBook;
//	ptr = this;
//}

//void UI::ChangeDataWindow::Cls_OnClose(HWND hwnd)
//{
//	EndDialog(hwnd, 0);
//}

//BOOL UI::ChangeDataWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
//{
//	using namespace UI;
//
//	SetWindowText(hwnd, TEXT("Add abonent"));
//	MoveWindow(hwnd, leftAbWnd, topAbWnd, widthAbWnd, heightAbWnd, 1);
//
//	GetClientRect(hwnd, &clientRect);
//	leftAb = clientRect.left + gap;
//	topAb = clientRect.top + gap;
//	widthAb = (clientRect.right - gap * 4) / 3;
//	heightAb = clientRect.bottom / 8;
//
//	SetOkCancel(hwnd);
//
//	HWND hAbonentGroup = CreateWindowEx(WS_EX_TRANSPARENT, TEXT("BUTTON"), TEXT("Information about abonent"),
//		WS_CHILD | WS_VISIBLE | BS_GROUPBOX, gap, gap, clientRect.right - 2 * gap, 220, hwnd, NULL, NULL, NULL);
//
//	SetName(hwnd);
//	SetGender(hwnd);
//	SetBirthDay(hwnd);
//	SetComment(hwnd);
//
//	HWND hPhoneGroup = CreateWindowEx(WS_EX_TRANSPARENT, TEXT("BUTTON"), TEXT("Phone list of this abonent"),
//		WS_CHILD | WS_VISIBLE | BS_GROUPBOX, gap, 250, 410, 330, hwnd, NULL, NULL, NULL);
//
//	hListPhone = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("LISTBOX"), 0,
//		WS_CHILD | WS_VISIBLE, 2 * gap, 280, 180, 200, hwnd, NULL, NULL, NULL);
//
//	SetNumberPhone(hwnd);
//	SetTypePhone(hwnd);
//	SetCommentPhone(hwnd);
//	SetInputButton(hwnd);
//	SetDeleteButton(hwnd);
//
//	return TRUE;
//}
//
//void UI::ChangeDataWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
//{
//	HWND h = GetFocus();
//
//	SetRadio(h);
//
//	if (h == hButtonAddConnect)
//	{
//		int lengthW = SendMessage(hEditPhone, WM_GETTEXTLENGTH, 0, 0);
//		if (lengthW == 0)
//		{
//			MessageBox(hwnd, TEXT("There is no a phone number!"), TEXT("Fill phone list"), MB_OK | MB_ICONSTOP);
//		}
//		else
//		{
//			TCHAR phoneRecord[1024];
//			wsprintf(phoneRecord, TEXT(""));
//
//			Connection connection = SetRecordToPhoneList(phoneRecord);
//
//			tempPhoneRepository.push_back(connection);
//
//
//			if (lstrlen(phoneRecord))
//			{
//				int index = SendMessage(hListPhone, LB_FINDSTRINGEXACT, -1, LPARAM(phoneRecord));
//				if (index == LB_ERR)
//					SendMessage(hListPhone, LB_ADDSTRING, 0, LPARAM(phoneRecord));
//			}
//			SetFocus(hEditCommentPhone);
//			SetWindowText(hEditCommentPhone, TEXT(""));
//			SetWindowText(hEditPhone, TEXT(""));
//			EnableWindow(hButtonDeleteConnect, TRUE);
//		}
//	}
//
//	else if (h == hButtonDeleteConnect)
//	{
//		{
//			int index = SendMessage(hListPhone, LB_GETCURSEL, 0, 0);
//			if (index != LB_ERR)
//			{
//				SendMessage(hListPhone, LB_DELETESTRING, index, 0);
//				//TO DO: delete from tempPhoneRepository
//			}
//		}
//	}
//
//	else if (h == hOK)
//	{
//		int length = SendMessage(hEditName, WM_GETTEXTLENGTH, 0, 0);
//		if (length != 0)
//		{
//			TCHAR* buffer = new TCHAR[length + 1];
//			memset(buffer, 0, length + 1);
//			GetWindowText(hEditName, buffer, length + 1);
//
//			Abonent abonent(buffer);
//			delete[] buffer;
//
//			SetAbonentGender(abonent);
//			SetAbonentBirthday(abonent);
//			SetAbonentComment(abonent);
//
//			for (int i = 0; i < tempPhoneRepository.size(); ++i)
//			{
//				abonent.AddConnection(tempPhoneRepository[i]);
//			}
//			tempPhoneRepository.clear();
//
//			myPhoneBook->AddAbonent(&abonent);
//
//			SendMessage(hwnd, WM_CLOSE, 0, 0);
//			DialogBox(0, MAKEINTRESOURCE(IDD_SPLASH), NULL, UI::MainWindow::dlgProc);
//		}
//		else
//		{
//			MessageBox(hwnd, TEXT("There is no abonent name!"), TEXT("Fill abonent information"), MB_OK | MB_ICONSTOP);
//		}
//	}
//
//	if (h == hCancel)
//	{
//		SendMessage(hwnd, WM_CLOSE, 0, 0);
//		DialogBox(0, MAKEINTRESOURCE(IDD_SPLASH), NULL, UI::MainWindow::dlgProc);
//	}
//}
//
//BOOL CALLBACK UI::ChangeDataWindow::dlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
//		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
//		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
//	}
//	return FALSE;
//}