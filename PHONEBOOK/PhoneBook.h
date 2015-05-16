#pragma once
#include "Splash.h"

class PhoneBook
{
private:	
	std::vector<Abonent*>abonentRepository;
public:
	~PhoneBook();
	bool AddAbonent(Abonent* newAbonent);
	TCHAR* GetAbonentName(INT index);
	INT GetBookSize(); 
	TCHAR* FindAbonentData(TCHAR*buffer);
};
