#pragma once
#include "Person.h"

class Doctor : public Person
{
	private:
		string license_number;
		string specialization;

	public:
		Doctor(string imie="", string nazwisko="", string pesel="", string licencja = "", string specjalizacja = "");
		~Doctor();
		string getLicense();
		string getSpecialization();
		void setLicense(string licencja);
		void setSpecialization(string specjalizacja);
		void read(ifstream& plik);
		void write(ofstream& plik);
		void info();
		void edit();
		void editNew();
		int type();
};

