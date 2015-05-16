#include"MainWindow.h"

UI::MainWindow* UI::MainWindow::ptr = NULL;

UI::MainWindow::MainWindow(PhoneBook* myPhoneBook)
{
	this->myPhoneBook = myPhoneBook;
	ptr = this;
}

void UI::MainWindow::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL UI::MainWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	using namespace UI;

	HWND hOK = GetDlgItem(hwnd, IDOK);
	DestroyWindow(hOK);
	HWND hCancel = GetDlgItem(hwnd, IDCANCEL);
	DestroyWindow(hCancel);

	GetClientRect(hwnd, &clientRectM);		
	left = clientRectM.left + gap;
	top = clientRectM.top + gap;
	width = (clientRectM.right - gap * 4) / 3;
	height = clientRectM.bottom / 8;

	SetButtons(hwnd);

	HWND hAbonentGroup = CreateWindowEx(WS_EX_TRANSPARENT, TEXT("BUTTON"), TEXT("Abonent list"),
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX, left, height + 2 * gap, clientRectM.right - gap * 1.5,
		clientRectM.bottom - height - gap * 3, hwnd, NULL, NULL, NULL);

	SetAbonentList(hwnd);
	SetAbonentData(hwnd);
		
	return TRUE;
}

void UI::MainWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HWND h = GetFocus();
	if (h == hButtonAdd)
	{
		SendMessage(hwnd, WM_CLOSE, 0, 0);
		DialogBox(0, MAKEINTRESOURCE(IDD_SPLASH), NULL, UI::AddAbonentWindow::dlgProc);
	}
		
	if (h == hCombo && codeNotify == CBN_SELCHANGE)	
		SetAbonentDataList(hwnd);

	if (h == hButtonDelete)
	{
		
		int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
		if (index != CB_ERR)
		{
			TCHAR *pBuffer = new TCHAR[128 + 1];
			SendMessage(hCombo, CB_GETLBTEXT, index, LPARAM(pBuffer));

			MessageBox(hwnd, pBuffer, TEXT("Remove the abonent"), MB_OK | MB_ICONINFORMATION);

			SendMessage(hCombo, CB_DELETESTRING, index, 0);
			SetWindowText(hEdit, 0);
			delete[] pBuffer;
		}
		if (myPhoneBook->GetBookSize() == 0)
		{
			MessageBox(hwnd, TEXT("Any abonent is not chosen! Select from Combo Box."),
				TEXT("Remove the abonent"), MB_OK | MB_ICONSTOP);
		}
	}

	if (h == hButtonChange)
	{
		int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
		if (index != CB_ERR)
		{
			TCHAR *pBuffer = new TCHAR[128 + 1];
			SendMessage(hCombo, CB_GETLBTEXT, index, LPARAM(pBuffer));


			//MessageBox(hwnd, pBuffer, TEXT("Change this abonent information"), MB_OK | MB_ICONINFORMATION);
			MessageBox(hwnd, pBuffer, TEXT("TO DO"), MB_OK | MB_ICONINFORMATION);
			//SendMessage(hwnd, WM_CLOSE, 0, 0);
			//DialogBox(0, MAKEINTRESOURCE(IDD_SPLASH), NULL, UI::AddAbonentWindow::dlgProc);

			//TO DO




			delete[] pBuffer;
		}
		if (myPhoneBook->GetBookSize() == 0)
		{
			MessageBox(hwnd, TEXT("Any abonent is not chosen! Select from Combo Box."),
				TEXT("Change this abonent information"), MB_OK | MB_ICONSTOP);
		}
	}
}

BOOL CALLBACK UI::MainWindow::dlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

void UI::MainWindow::SetButtons(HWND hwnd)
{

	hButtonAdd = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Add abonent"), WS_CHILD | WS_VISIBLE | BS_MULTILINE,
		left, top, width, height, hwnd, 0, 0, 0);

	hButtonDelete = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Delete abonent"), WS_CHILD | WS_VISIBLE | BS_MULTILINE,
		2 * left + width, top, width, height, hwnd, 0, 0, 0);

	hButtonChange = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Change data"), WS_CHILD | WS_VISIBLE | BS_MULTILINE,
		3 * left + 2 * width, top, width, height, hwnd, 0, 0, 0);
}

void UI::MainWindow::SetAbonentList(HWND hwnd)
{
	HWND hStaticAbonentName = CreateWindowEx(0, TEXT("STATIC"), TEXT("Select from Combo Box:"),
		WS_CHILD | WS_VISIBLE | BS_RIGHT,
		32, 64, 160, 30, hwnd, NULL, NULL, NULL);

	hCombo = CreateWindowEx(WS_EX_DLGMODALFRAME, TEXT("COMBOBOX"), 0,
		WS_CHILD | WS_VISIBLE | CBS_SORT | CBS_DROPDOWNLIST | WS_VSCROLL,
		left + gap, height + gap + 50, clientRectM.right / 2 - gap * 1.5 - gap,
		clientRectM.bottom - height - gap * 2, hwnd, NULL, NULL, NULL);

	INT bookSize = myPhoneBook->GetBookSize();
	for (INT i = 0; i < bookSize; ++i)
		SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(myPhoneBook->GetAbonentName(i)));
}

void UI::MainWindow::SetAbonentData(HWND hwnd)
{
	HWND hStaticAbonentData = CreateWindowEx(0, TEXT("STATIC"), TEXT("Abonent data:"),
		WS_CHILD | WS_VISIBLE | BS_RIGHT,
		clientRectM.right / 2 + gap  * .5 + 20, 64, 100, 30, hwnd, NULL, NULL, NULL);
	
	hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL,
		clientRectM.right / 2 + gap * .5, height + gap + 50,
		clientRectM.right / 2 - gap * 1.5 - gap, clientRectM.bottom - height - gap * 2 - 57, hwnd, NULL, NULL, NULL);
}

void UI::MainWindow::SetAbonentDataList(HWND hwnd)
{
	SendMessage(hEdit, LB_RESETCONTENT, 0, 0);
	int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
	if (index != CB_ERR)
	{
		int length = SendMessage(hCombo, CB_GETLBTEXTLEN, index, 0);
		TCHAR* pBuffer = new TCHAR[length + 1];
		SendMessage(hCombo, CB_GETLBTEXT, index, LPARAM(pBuffer));		

		SetWindowText(hEdit, myPhoneBook->FindAbonentData(pBuffer));

		delete[] pBuffer;
	}
}