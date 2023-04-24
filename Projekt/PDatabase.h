#pragma once
#include "Doctor.h"
#include "Patient.h"

class PDatabase
{
	private:
		vector<Person*> PersonsBase;

	public:
		PDatabase();
		~PDatabase();
		vector<Person*>* getBase();
		void addDoctor();
		void addPatient();
		void editPerson();
		void removePerson();
		void readAll();
		void saveAll();
		void showAll(int x);
		void show(int x);
		Person* getPersonOA(int x);
		int find(string x);
		void sort(int x);
		void sort(int x, int y);
		
};

