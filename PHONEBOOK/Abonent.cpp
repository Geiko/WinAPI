#include "Abonent.h"

Abonent::Abonent(TCHAR* name)
{
	this->name = new TCHAR[200];
	wsprintf(this->name, TEXT(""));
	wcscat_s(this->name, 200, name);

	gender = new TCHAR[30];
	wsprintf(gender, TEXT(""));

	birthday = new TCHAR[128];
	wsprintf(birthday, TEXT(""));

	comment = new TCHAR[300];
	wsprintf(comment, TEXT(""));
}

Abonent::~Abonent(){}

void Abonent::PutGender(TCHAR* gender)
{
	wcscat_s(this->gender, 30, gender);
}

void Abonent::PutBirthday(TCHAR* birthday)
{
	wcscat_s(this->birthday, 128, birthday);
}

void Abonent::PutComment(TCHAR* comment)
{
	wcscat_s(this->comment, 300, comment);
	TCHAR tmp[16];
	wsprintf(tmp, TEXT("\r\n"));
	wcscat_s(this->comment, 300, tmp);
}

void Abonent::PutConnectList(Connection connection)
{
	phoneRepository.push_back(connection);
}

void Abonent::AddConnection(Connection c)
{
	phoneRepository.push_back(c);
}