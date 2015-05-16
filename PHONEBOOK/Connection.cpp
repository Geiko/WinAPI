#include "Connection.h"

Connection::Connection(TCHAR* phone, TCHAR* phoneType, TCHAR* commentPh)
{
	this->phone = new TCHAR[100];
	wsprintf(this->phone, TEXT(""));
	wcscat_s(this->phone, 100, phone);

	this->phoneType = new TCHAR[20];
	wsprintf(this->phoneType, TEXT(""));
	wcscat_s(this->phoneType, 20, phoneType);

	this->commentPh = new TCHAR[500];
	wsprintf(this->commentPh, TEXT(""));
	wcscat_s(this->commentPh, 500, commentPh);
}

Connection::~Connection(){}


TCHAR* Connection::GetPhoneType()
{
	return phoneType;
}

TCHAR*  Connection::GetPhone()
{
	return phone;
}

TCHAR*  Connection::GetCommentPh()
{
	return commentPh;
}