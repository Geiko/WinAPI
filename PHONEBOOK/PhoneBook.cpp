#include "PhoneBook.h"

PhoneBook::~PhoneBook(){}

bool PhoneBook::AddAbonent(Abonent* newAbonent)
{
	abonentRepository.push_back(newAbonent);
	return TRUE;
}

TCHAR* PhoneBook::GetAbonentName(INT index)
{
	return abonentRepository[index]->name;
}

INT PhoneBook::GetBookSize()
{
	return abonentRepository.size();
}

TCHAR* PhoneBook::FindAbonentData(TCHAR* buffer)
{
	TCHAR abonentData[2048];
	wsprintf(abonentData, TEXT(""));
	for (int i = 0; i < abonentRepository.size(); ++i)
	{
		if (wcscmp(buffer, abonentRepository[i]->name) == 0)
		{
			wcscat_s(abonentData, 2048, abonentRepository[i]->gender);
			wcscat_s(abonentData, 2048, abonentRepository[i]->birthday);
			wcscat_s(abonentData, 2048, abonentRepository[i]->comment);

			int tmp = abonentRepository[i]->phoneRepository.size();
			for (int j = 0; j < tmp; ++j)
			{
				wcscat_s(abonentData, 2048, abonentRepository[i]->phoneRepository[j].GetPhoneType());
				wcscat_s(abonentData, 2048, abonentRepository[i]->phoneRepository[j].GetPhone());
				wcscat_s(abonentData, 2048, abonentRepository[i]->phoneRepository[j].GetCommentPh());
			}

			return abonentData;
		}
	}
	return NULL;
}