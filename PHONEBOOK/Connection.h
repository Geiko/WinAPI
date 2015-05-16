#pragma once
#include "Splash.h"

class Connection
{
private:
	TCHAR* phone;
	TCHAR* phoneType;
	TCHAR* commentPh;
public:
	Connection(TCHAR* phone, TCHAR* phoneType, TCHAR* commentPh);
	~Connection();
	TCHAR* GetPhone();
	TCHAR* GetPhoneType();
	TCHAR* GetCommentPh();
};