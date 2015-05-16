#include"AddAbonentWindow.h"

UI::AddAbonentWindow* UI::AddAbonentWindow::ptr = NULL;

UI::AddAbonentWindow::AddAbonentWindow(PhoneBook* myPhoneBook)
{
	this->myPhoneBook = myPhoneBook;
	ptr = this;
}

void UI::AddAbonentWindow::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL UI::AddAbonentWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	using namespace UI;

	SetWindowText(hwnd, TEXT("Add abonent"));
	MoveWindow(hwnd, leftAbWnd, topAbWnd, widthAbWnd, heightAbWnd, 1);

	GetClientRect(hwnd, &clientRect);
	leftAb = clientRect.left + gap;
	topAb = clientRect.top + gap;
	widthAb = (clientRect.right - gap * 4) / 3;
	heightAb = clientRect.bottom / 8;

	SetOkCancel(hwnd);
	
	HWND hAbonentGroup = CreateWindowEx(WS_EX_TRANSPARENT, TEXT("BUTTON"), TEXT("Information about abonent"),
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX, gap, gap, clientRect.right - 2 * gap, 220, hwnd, NULL, NULL, NULL);

	SetName(hwnd);
	SetGender(hwnd);
	SetBirthDay(hwnd);
	SetComment(hwnd);

	HWND hPhoneGroup = CreateWindowEx(WS_EX_TRANSPARENT, TEXT("BUTTON"), TEXT("Phone list of this abonent"),
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX, gap, 250, 410, 330, hwnd, NULL, NULL, NULL);

	hListPhone = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("LISTBOX"), 0,
		WS_CHILD | WS_VISIBLE , 2 * gap, 280, 180, 200, hwnd, NULL, NULL, NULL);

	SetNumberPhone(hwnd);
	SetTypePhone(hwnd);
	SetCommentPhone(hwnd);
	SetInputButton(hwnd);
	SetDeleteButton(hwnd);

	return TRUE;
}

void UI::AddAbonentWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HWND h = GetFocus();

	SetRadio(h);	
	
	if (h == hButtonAddConnect)
	{
		int lengthW = SendMessage(hEditPhone, WM_GETTEXTLENGTH, 0, 0);
		if (lengthW == 0)
		{
			MessageBox(hwnd, TEXT("There is no a phone number!"), TEXT("Fill phone list"), MB_OK | MB_ICONSTOP);
		}
		else
		{
			TCHAR phoneRecord[1024];
			wsprintf(phoneRecord, TEXT(""));

			Connection connection = SetRecordToPhoneList(phoneRecord);

			tempPhoneRepository.push_back(connection);


			if (lstrlen(phoneRecord))
			{
				int index = SendMessage(hListPhone, LB_FINDSTRINGEXACT, -1, LPARAM(phoneRecord));
				if (index == LB_ERR)
					SendMessage(hListPhone, LB_ADDSTRING, 0, LPARAM(phoneRecord));
			}
			SetFocus(hEditCommentPhone);
			SetWindowText(hEditCommentPhone, TEXT(""));
			SetWindowText(hEditPhone, TEXT(""));
			EnableWindow(hButtonDeleteConnect, TRUE);
		}
	}

	else if (h == hButtonDeleteConnect)
	{
		{
			int index = SendMessage(hListPhone, LB_GETCURSEL, 0, 0);
			if (index != LB_ERR) 
			{
				SendMessage(hListPhone, LB_DELETESTRING, index, 0);
				//TO DO: delete from tempPhoneRepository
			}
		}
	}

	else if (h == hOK)
	{
		int length = SendMessage(hEditName, WM_GETTEXTLENGTH, 0, 0);
		if (length != 0)
		{
			TCHAR* buffer = new TCHAR[length + 1];
			memset(buffer, 0, length + 1);
			GetWindowText(hEditName, buffer, length + 1);

			Abonent abonent(buffer);
			delete[] buffer;

			SetAbonentGender(abonent);
			SetAbonentBirthday(abonent);
			SetAbonentComment(abonent);

			for (int i = 0; i < tempPhoneRepository.size(); ++i)
			{
				abonent.AddConnection(tempPhoneRepository[i]);
			}
			tempPhoneRepository.clear();

			myPhoneBook->AddAbonent(&abonent);

			SendMessage(hwnd, WM_CLOSE, 0, 0);
			DialogBox(0, MAKEINTRESOURCE(IDD_SPLASH), NULL, UI::MainWindow::dlgProc);
		}
		else
		{
			MessageBox(hwnd, TEXT("There is no abonent name!"), TEXT("Fill abonent information"), MB_OK | MB_ICONSTOP);
		}
	}

	if (h == hCancel)
	{
		SendMessage(hwnd, WM_CLOSE, 0, 0);
		DialogBox(0, MAKEINTRESOURCE(IDD_SPLASH), NULL, UI::MainWindow::dlgProc);
	}
}

BOOL CALLBACK UI::AddAbonentWindow::dlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

void UI::AddAbonentWindow::SetOkCancel(HWND hwnd)
{
	hOK = GetDlgItem(hwnd, IDOK);
	MoveWindow(hOK, clientRect.right - 155, clientRect.bottom - 35, 70, 25, 1);
	hCancel = GetDlgItem(hwnd, IDCANCEL);
	MoveWindow(hCancel, clientRect.right - 80, clientRect.bottom - 35, 70, 25, 1);
}

void UI::AddAbonentWindow::SetName(HWND hwnd)
{
	HWND hStaticName = CreateWindowEx(0, TEXT("STATIC"), TEXT("Abonent name:"),
		WS_CHILD | WS_VISIBLE | BS_RIGHT,
		16, 30, 100, 30, hwnd, NULL, NULL, NULL);
	hEditName = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL,
		120, 30, 280, 30, hwnd, NULL, NULL, NULL);
}

void UI::AddAbonentWindow::SetGender(HWND hwnd)
{
	HWND hGroup2 = CreateWindowEx(WS_EX_TRANSPARENT, TEXT("BUTTON"), TEXT("Gender"),
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX, gap + 3, 65, 110, 90, hwnd, NULL, NULL, NULL);
	hRadio1 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("male"),
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON | WS_GROUP | WS_TABSTOP,
		16, 80, 90, 30, hwnd, NULL, NULL, NULL);
	hRadio2 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("female"),
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		16, 100, 90, 30, hwnd, NULL, NULL, NULL);
	hRadio3 = CreateWindowEx(0, TEXT("BUTTON"), TEXT("don't point"),
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		16, 120, 90, 30, hwnd, NULL, NULL, NULL);
	SendMessage(hRadio3, BM_SETCHECK, 1, 0);

	genderVector.push_back(hRadio1);
	genderVector.push_back(hRadio2);
	genderVector.push_back(hRadio3);
}

void UI::AddAbonentWindow::SetBirthDay(HWND hwnd)
{
	HWND hGroup3 = CreateWindowEx(WS_EX_TRANSPARENT, TEXT("BUTTON"), TEXT("Birthday"),
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 116, 65, 297, 90, hwnd, NULL, NULL, NULL);
	HWND hStaticDay = CreateWindowEx(0, TEXT("STATIC"), TEXT("day"),
		WS_CHILD | WS_VISIBLE | BS_RIGHT,
		150, 90, 50, 20, hwnd, NULL, NULL, NULL);
	hCombo1 = CreateWindowEx(WS_EX_DLGMODALFRAME, TEXT("COMBOBOX"), 0,
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP,
		140, 110, 50, 300, hwnd, NULL, NULL, NULL);
	TCHAR temp[3];
	for (INT i = 1; i < 32; ++i)
	{
		_itow_s(i, temp, 10);
		SendMessage(hCombo1, CB_ADDSTRING, 0, LPARAM(temp));
	}

	HWND hStaticMonth = CreateWindowEx(0, TEXT("STATIC"), TEXT("month"),
		WS_CHILD | WS_VISIBLE | BS_RIGHT,
		235, 90, 50, 20, hwnd, NULL, NULL, NULL);
	hCombo2 = CreateWindowEx(WS_EX_DLGMODALFRAME, TEXT("COMBOBOX"), 0,
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP,
		215, 110, 80, 500, hwnd, NULL, NULL, NULL);
	SendMessage(hCombo2, CB_ADDSTRING, 0, LPARAM(TEXT("January")));
	SendMessage(hCombo2, CB_ADDSTRING, 0, LPARAM(TEXT("February")));
	SendMessage(hCombo2, CB_ADDSTRING, 0, LPARAM(TEXT("Marth")));
	SendMessage(hCombo2, CB_ADDSTRING, 0, LPARAM(TEXT("April")));
	SendMessage(hCombo2, CB_ADDSTRING, 0, LPARAM(TEXT("May")));
	SendMessage(hCombo2, CB_ADDSTRING, 0, LPARAM(TEXT("June")));
	SendMessage(hCombo2, CB_ADDSTRING, 0, LPARAM(TEXT("July")));
	SendMessage(hCombo2, CB_ADDSTRING, 0, LPARAM(TEXT("August")));
	SendMessage(hCombo2, CB_ADDSTRING, 0, LPARAM(TEXT("September")));
	SendMessage(hCombo2, CB_ADDSTRING, 0, LPARAM(TEXT("October")));
	SendMessage(hCombo2, CB_ADDSTRING, 0, LPARAM(TEXT("November")));
	SendMessage(hCombo2, CB_ADDSTRING, 0, LPARAM(TEXT("December")));

	HWND hStaticYear = CreateWindowEx(0, TEXT("STATIC"), TEXT("year"),
		WS_CHILD | WS_VISIBLE | BS_RIGHT,
		340, 90, 40, 20, hwnd, NULL, NULL, NULL);
	hCombo3 = CreateWindowEx(WS_EX_DLGMODALFRAME, TEXT("COMBOBOX"), 0,
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP | WS_VSCROLL,
		320, 110, 70, 300, hwnd, NULL, NULL, NULL);
	TCHAR temp1[7];
	for (INT i = 2015; i > 1900; --i)
	{
		_itow_s(i, temp1, 10);
		SendMessage(hCombo3, CB_ADDSTRING, 0, LPARAM(temp1));
	}
}

void UI::AddAbonentWindow::SetComment(HWND hwnd)
{
	HWND hStaticName = CreateWindowEx(0, TEXT("STATIC"), TEXT("Comment :"),
		WS_CHILD | WS_VISIBLE | BS_RIGHT,
		16, 165, 90, 30, hwnd, NULL, NULL, NULL);
	hEditComment = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_MULTILINE,
		120, 165, 280, 50, hwnd, NULL, NULL, NULL);
}

void UI::AddAbonentWindow::SetNumberPhone(HWND hwnd)
{
	HWND hStaticName = CreateWindowEx(0, TEXT("STATIC"), TEXT("Input connection number :"),
		WS_CHILD | WS_VISIBLE | BS_RIGHT,
		230, 285, 200, 30, hwnd, NULL, NULL, NULL);

	hEditPhone = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_MULTILINE,
		220, 310, 180, 30, hwnd, NULL, NULL, NULL);
}

void UI::AddAbonentWindow::SetTypePhone(HWND hwnd)
{
	HWND hStaticTypePhone = CreateWindowEx(0, TEXT("STATIC"), TEXT("Phone type:"),
		WS_CHILD | WS_VISIBLE | BS_RIGHT,
		230, 360, 80, 20, hwnd, NULL, NULL, NULL);

	hComboTypePhone = CreateWindowEx(WS_EX_DLGMODALFRAME, TEXT("COMBOBOX"), 0,
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_TABSTOP,
		313, 360, 80, 300, hwnd, NULL, NULL, NULL);

	SendMessage(hComboTypePhone, CB_ADDSTRING, 0, LPARAM(TEXT("Mobile")));
	SendMessage(hComboTypePhone, CB_ADDSTRING, 0, LPARAM(TEXT("Home")));
	SendMessage(hComboTypePhone, CB_ADDSTRING, 0, LPARAM(TEXT("Work")));
	SendMessage(hComboTypePhone, CB_ADDSTRING, 0, LPARAM(TEXT("Skype")));
	SendMessage(hComboTypePhone, CB_ADDSTRING, 0, LPARAM(TEXT("Hangouts")));
	SendMessage(hComboTypePhone, CB_ADDSTRING, 0, LPARAM(TEXT("ISQ")));
	SendMessage(hComboTypePhone, CB_ADDSTRING, 0, LPARAM(TEXT("Viber")));
	SendMessage(hComboTypePhone, CB_ADDSTRING, 0, LPARAM(TEXT("e-mail")));
}

void UI::AddAbonentWindow::SetCommentPhone(HWND hwnd)
{
	HWND hStaticName = CreateWindowEx(0, TEXT("STATIC"), TEXT("Comment :"),
		WS_CHILD | WS_VISIBLE | BS_RIGHT, 
		230, 395, 90, 30, hwnd, NULL, NULL, NULL);

	hEditCommentPhone = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_MULTILINE,
		220, 420, 180, 80, hwnd, NULL, NULL, NULL);
}

void UI::AddAbonentWindow::SetInputButton(HWND hwnd)
{
	hButtonAddConnect = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Add this connection"), WS_CHILD | WS_VISIBLE | BS_MULTILINE,
		220, 520, 180, 40, hwnd, 0, 0, 0);

	HWND hNewPhone = CreateWindowEx(WS_EX_TRANSPARENT, TEXT("BUTTON"), TEXT("Create new connection"),
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 210, 270, 200, 300, hwnd, NULL, NULL, NULL);
}

void UI::AddAbonentWindow::SetDeleteButton(HWND hwnd)
{
	HWND hDeletePhone = CreateWindowEx(WS_EX_TRANSPARENT, TEXT("BUTTON"), TEXT("Select from list"),
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 2 * gap, 500, 180, 70, hwnd, NULL, NULL, NULL);

	hButtonDeleteConnect = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"),
		TEXT("Delete this connection"), WS_CHILD | WS_VISIBLE | BS_MULTILINE,
		2 * gap + 10, 520, 160, 40, hwnd, 0, 0, 0);

	EnableWindow(hButtonDeleteConnect, FALSE);
}


void UI::AddAbonentWindow::SetRadio(HWND h)
{
	int sizeGender = genderVector.size();
	for (int j = 0; j < sizeGender; ++j)
	{
		if (h == genderVector[j])
		{
			for (int i = 0; i < sizeGender; ++i)
			{
				if (i == j) SendMessage(genderVector[i], BM_SETCHECK, 1, 0);
				else
				{
					SendMessage(genderVector[i], BM_SETCHECK, 0, 0);
				}
			}
		}
	}
}

void UI::AddAbonentWindow::SetAbonentGender(Abonent& abonent)
{
	int sizeGender = genderVector.size();
	LRESULT result;
	for (int i = 0; i < sizeGender; ++i)
	{
		result = SendMessage(genderVector[i], BM_GETCHECK, 0, 0);
		if (result == BST_CHECKED && i == 0)
		{
			abonent.PutGender(TEXT("GENDER:  male"));
			break;
		}
		else if (result == BST_CHECKED && i == 1)
		{
			abonent.PutGender(TEXT("GENDER:  female"));
			break;
		}
		else if (result == BST_CHECKED && i == 2)
		{
			abonent.PutGender(TEXT("GENDER:  don't point"));
			break;
		}
	}
	genderVector.clear();
}

void UI::AddAbonentWindow::SetAbonentBirthday(Abonent& abonent)
{
	TCHAR birthday[128];
	wsprintf(birthday, TEXT("\r\nBIRTHDAY:  "));

	int index1 = SendMessage(hCombo1, CB_GETCURSEL, 0, 0);
	if (index1 != CB_ERR)
	{
	int length1 = SendMessage(hCombo1, CB_GETLBTEXTLEN, index1, 0);
		TCHAR* pBuffer1 = new TCHAR[length1 + 1];
		SendMessage(hCombo1, CB_GETLBTEXT, index1, LPARAM(pBuffer1));
		wcscat_s(birthday, 64, pBuffer1);
		delete[] pBuffer1;
	}

	wcscat_s(birthday, 128, TEXT(" "));

	int index2 = SendMessage(hCombo2, CB_GETCURSEL, 0, 0);
	if (index2 != CB_ERR)
	{
		int length2 = SendMessage(hCombo2, CB_GETLBTEXTLEN, index2, 0);
		TCHAR* pBuffer2 = new TCHAR[length2 + 1];
		SendMessage(hCombo2, CB_GETLBTEXT, index2, LPARAM(pBuffer2));
		wcscat_s(birthday, 34, pBuffer2);
		delete[] pBuffer2;
	}

	wcscat_s(birthday, 128, TEXT(" "));

	int index3 = SendMessage(hCombo2, CB_GETCURSEL, 0, 0);
	if (index3 != CB_ERR)
	{
		int length3 = SendMessage(hCombo3, CB_GETLBTEXTLEN, index3, 0);
		TCHAR* pBuffer3 = new TCHAR[length3 + 1];
		SendMessage(hCombo3, CB_GETLBTEXT, index3, LPARAM(pBuffer3));
		wcscat_s(birthday, 128, pBuffer3);
		delete[] pBuffer3;
	}
	abonent.PutBirthday(birthday);
}

void UI::AddAbonentWindow::SetAbonentComment(Abonent& abonent)
{
	TCHAR comment[300];
	wsprintf(comment, TEXT("\r\nCOMMENT:  "));
	TCHAR temp[300];
	GetWindowText(hEditComment, temp, 300);
	wcscat_s(comment, 128, temp);
	abonent.PutComment(comment);
}

Connection  UI::AddAbonentWindow::SetRecordToPhoneList(TCHAR* phoneRecord)
{
	TCHAR phoneType[64];
	wsprintf(phoneType, TEXT("\r\n"));
	int indexL = SendMessage(hComboTypePhone, CB_GETCURSEL, 0, 0);
	if (indexL != CB_ERR)
	{
		int lengthL = SendMessage(hComboTypePhone, CB_GETLBTEXTLEN, indexL, 0);
		TCHAR* pBufferL = new TCHAR[lengthL + 1];
		SendMessage(hComboTypePhone, CB_GETLBTEXT, indexL, LPARAM(pBufferL));
		wcscat_s(phoneType, 64, pBufferL);
		delete[] pBufferL;
	} 

	TCHAR temp[5];
	wsprintf(temp, TEXT(": "));
	wcscat_s(phoneType, 64, temp);
	wcscat_s(phoneRecord, 1024, phoneType);

	TCHAR phone[128];
	wsprintf(phone, TEXT(""));
	GetWindowText(hEditPhone, phone, 128);
	wcscat_s(phoneRecord, 1024, phone);

	TCHAR temp2[1024];
	wsprintf(temp2, TEXT(""));
	TCHAR commentPh[1024];
	wsprintf(commentPh, TEXT(" ("));
	GetWindowText(hEditCommentPhone, temp2, 1024);
	wcscat_s(commentPh, 1024, temp2);
	TCHAR temp3[10];
	wsprintf(temp3, TEXT(")"));
	wcscat_s(commentPh, 1024, temp3);
	wcscat_s(phoneRecord, 1024, commentPh);
	
	Connection connection(phone, phoneType, commentPh); 
	
	return connection;
}