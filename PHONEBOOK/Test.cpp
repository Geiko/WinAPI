#pragma once
#include"Splash.h"


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR cmdLine, int nCmdShow){

	PhoneBook myPhoneBook;
	UI::Splash splash;
	UI::MainWindow mainWnd(&myPhoneBook);
	UI::AddAbonentWindow addAbonent(&myPhoneBook);
	
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_SPLASH), NULL, UI::Splash::dlgProc);
}

