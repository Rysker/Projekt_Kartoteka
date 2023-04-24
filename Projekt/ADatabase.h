#pragma once
#include "Appointment.h"
#include "Patient.h"
#include "VFunctions.h"
#include "PDatabase.h"

class ADatabase
{
private:
	vector<Appointment*> Visits;

public:
	ADatabase();
	~ADatabase();
	vector<Appointment*>* getBase();
	void addAppointment();
	void editAppointment();
	void removeAppointment();
	void removeAppointment(string t);
	void removeAppointmentAt(int x);
	void convertToVisit(int id);
	void readAll();
	void saveAll();
	int find(string ID);
	void showAll();
	void show();
	void markDoctor(string ID);
};