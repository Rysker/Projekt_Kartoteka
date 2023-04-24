#pragma once
#include "Person.h"

class Patient : public Person
{
	private:
		int age;
		string phonenumber;

	public:
		Patient(int id = 0, string imie = "", string nazwisko = "", string pesel = "", int age = 0, string number = "");
		~Patient();
		int getAge();
		string getPhonenumber();
		void setAge(int age);
		void setPnumber(string number);
		void info();
		void read(ifstream& plik);
		void write(ofstream& plik);
		void edit();
		void editNew();
		int type();
};

