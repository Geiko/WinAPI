#pragma once
#include "Splash.h"

class Connection;
class Abonent
{
	friend class PhoneBook;
private:
	TCHAR* name;
	TCHAR* gender;
	TCHAR* birthday;		
	TCHAR* comment;
	std::vector<Connection>phoneRepository;

public:
	Abonent(TCHAR* name);
	~Abonent();
	void PutGender(TCHAR* gender);
	void PutBirthday(TCHAR* birthday);
	void PutComment(TCHAR* comment);
	void PutConnectList(Connection connection);
	void AddConnection(Connection c);
};