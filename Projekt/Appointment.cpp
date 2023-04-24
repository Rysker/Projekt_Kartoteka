#include "Appointment.h"

Appointment::Appointment(string id1, string id2, string id3, string id4, bool cbs) :
	patient_id(id2), doctor_id(id3), uniqueAppointmentID(id4), cbs(cbs) {}
Appointment::~Appointment() {}

string Appointment::getPatientid() { return this->patient_id; }
string Appointment::getDoctorid() { return this->doctor_id; }
string Appointment::getUniqueAppointmentID() { return this->uniqueAppointmentID; }

void Appointment::setPatientid(string t) { this->patient_id = t; }
void Appointment::setDoctorid(string t) { this->doctor_id = t; }
void Appointment::setUniqueAppointmentID(string t) { this->uniqueAppointmentID = t; }

/**
 * Invoked when we want to edit already existing record
 * 
 */
void Appointment::editAppointment()
{
	string t;
	cout << "ENTER bez podania innego znaku pominie edycje pola\nDane w blednym formacie nie zostana zapisane\n";
	if ((t = getStringEdit("ID pacjenta")) != "")
	{
		this->setPatientid(t);
	}
	if ((t = getStringEdit("ID lekarza")) != "")
	{
		this->setDoctorid(t);
	}
}
/**
 * Displays all of the information about record
 * 
 */
void Appointment::info()
{
	cout << *this;
}
/**
 * This function read all information about record to the file
 *
 * \param plik Name of file
 */
void Appointment::read(ifstream& plik)
{
	int string_size;
	int odczyt_int;
	string odczyt_string;
	if (plik.good())
	{
		plik.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
		odczyt_string.resize(string_size);
		plik.read(reinterpret_cast<char*>(&odczyt_string[0]), string_size);
		this->setUniqueAppointmentID(odczyt_string);

		plik.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
		odczyt_string.resize(string_size);
		plik.read(reinterpret_cast<char*>(&odczyt_string[0]), string_size);
		this->setPatientid(odczyt_string);

		plik.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
		odczyt_string.resize(string_size);
		plik.read(reinterpret_cast<char*>(&odczyt_string[0]), string_size);
		this->setDoctorid(odczyt_string);
	}
}
/**
 * This function writes all information about record to the file
 *
 * \param plik Name of file
 */
void Appointment::write(ofstream& plik)
{
	int string_size;
	int odczyt_int;
	string odczyt_string;
    if (plik.good())
    {
		string_size = uniqueAppointmentID.length();
		plik.write(reinterpret_cast<char*>(&string_size), sizeof(string_size));
		plik.write(reinterpret_cast<char*>(&uniqueAppointmentID[0]), string_size);
		
		string_size = patient_id.length();
		plik.write(reinterpret_cast<char*>(&string_size), sizeof(string_size));
		plik.write(reinterpret_cast<char*>(&patient_id[0]), string_size);

		string_size = doctor_id.length();
		plik.write(reinterpret_cast<char*>(&string_size), sizeof(string_size));
		plik.write(reinterpret_cast<char*>(&doctor_id[0]), string_size);

    }
}
/**
 * Invoked when we want to edit new record
 * 
 */
void Appointment::editNewAppointment()
{
	string t;
	int i = 0;
	this->setDoctorid(getString("ID doktora"));
	this->setPatientid(getString("ID pacjenta"));
}
/**
 * Currently unused. Was supposed to mark record that could be saved.
 * 
 */
void Appointment::setCbs() { this->cbs = true; }

ostream& operator<<(ostream& lhs, const Appointment& rhs)
{
	lhs << rhs.uniqueAppointmentID << "\t\t";
	lhs << rhs.patient_id << "\t\t";
	lhs << rhs.doctor_id <<  endl;
	return lhs;
}
