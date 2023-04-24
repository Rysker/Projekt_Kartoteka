#pragma once
#include "Patient.h"
#include "Doctor.h"

class Appointment
{
	private:
		string uniqueAppointmentID;
		string patient_id;
		string doctor_id;
		bool cbs;

	public:
		Appointment(string id1 = "", string id2 = "", string id3 = "", string id4 = "", bool cbs = false);
		~Appointment();
		string getPatientid();
		string getDoctorid();
		string getUniqueAppointmentID();
		bool getCbs();
		void setPatientid(string t);
		void setDoctorid(string t);
		void setUniqueAppointmentID(string ID);
		void read(ifstream& plik);
		void write(ofstream& plik);
		void editAppointment();
		void editNewAppointment();
		void setCbs();
		void info();
		friend ostream& operator<<(ostream& lhs, const Appointment& rhs);
};

ostream& operator<<(ostream& lhs, const Appointment& rhs);

