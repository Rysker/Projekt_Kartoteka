#pragma once
#include "VFunctions.h"

class Person
{
	protected:
		string firstname;
		string lastname;
		string pesel;
		string uniqueFacilityID;
		bool cbs;

	public:
		Person(string firstname = "", string lastname = "", string pesel = "", string ID = "", bool cbs = false);
		virtual ~Person();
		string getFirstname();
		string getLastname();
		string getPesel();
		string getUniqueFacilityID();
		bool getCBS();
		void setFirstname(string imie);
		void setLastname(string nazwisko);
		void setPesel(string pesel);
		void setUniqueFacilityID(string t);
		void setCBS();
		virtual void info() = 0;
		virtual void read(ifstream& plik) = 0;
		virtual void write(ofstream& plik) = 0;
		virtual void edit() = 0;
		virtual void editNew() = 0;
		virtual int type() = 0;
};