#include "ADatabase.h"

extern bool NOSAVE;
extern bool NOEDIT;


template<class T>
void showAllRecords(vector<T*> v)
{
	for (auto item : v)
		item->info();
}

template<class T>
void saveAllRecords(vector<T*> v, string source)
{
	if (v.empty())
		return;
	ofstream source2{ source, ios::binary };
	source2.clear();
	v.back()->write(source2);
	v.pop_back();
	source2.close();
	ofstream source3{ source, ios::binary | ios::app };
	while (v.size() != 0)
	{
		v.back()->write(source3);
		v.pop_back();
	}
	source3.close();
}

extern PDatabase base;
ADatabase::ADatabase(){}
ADatabase::~ADatabase(){}

vector<Appointment*>* ADatabase::getBase() { return &(this->Visits); }
/**
 * Used when we want to create new Appointment.
 * 
 */
void ADatabase::addAppointment() 
{
	string t;
	Visits.push_back(new Appointment);
	Visits.back()->editNewAppointment();
	do
	{
		t = generateUniqueID('A');

	} while (find(t) != -1 && Visits.size() != 0);
	Visits.back()->setUniqueAppointmentID(t);
	Visits.back()->setCbs();
	if (base.find(Visits.back()->getDoctorid()) == -1 || base.find(Visits.back()->getPatientid()) == -1)
	{
		cout << "Podano bledny ID doktora lub pacjenta!\n";
		delete Visits.back();
		Visits.pop_back();
	}
	saveAll();
}
/**
 * Used when we want to edit already existing record
 * 
 */
void ADatabase::editAppointment() 
{
	if (NOEDIT == false)
	{

		Appointment tmp;
		string ID = getString("Unikatowe ID wizyty ktora chcesz edytowac");
		int y;
		if ((y = this->find(ID)) != -1)
		{
			cout << "Informacje o wizycie ktora chcesz edytowac:\n";
			Visits.at(y)->info();
			tmp = *Visits.at(y);
			Visits.at(y)->editAppointment();
			if ((base.find(Visits.at(y)->getDoctorid()) == -1) || (base.find(Visits.at(y)->getPatientid()) == -1))
			{
				cout << "Conajmniej jedno podane ID nie istnieje w bazie!\n";
				*Visits.at(y) = tmp;
			}
		}
		else
			cout << "Nie istnieje wizyta o podanym ID!" << endl;
	}
	else
		cout << "Mozliwosc edycji zostala wylaczona!\n";
}
/**
 * Removes appointment, but asks user for ID of visit he wants to delete
 * 
 */
void ADatabase::removeAppointment()
{
	string x = getString("ID wizyty ktora chcesz usunac");
	int y;
	if ((y = this->find(x)) != -1)
		this->removeAppointmentAt(y);
	else
		cout << "Nie istnieje wizyta o podanym ID!" << endl;
}
/**
 * Deletes appointment with given ID
 * 
 * \param t Unique ID of appointment we want to delete
 */
void ADatabase::removeAppointment(string t)
{
	for (int i = 0; i < Visits.size(); i++)
	{
		if (Visits.at(i)->getPatientid() == t)
			removeAppointmentAt(i);
	}
}
/**
 * Removes record from vector 
 * 
 * \param x Number of index at which given record is
 */
void ADatabase::removeAppointmentAt(int x)
{
	delete Visits.at(x);
	Visits.erase(Visits.begin() + x);
}
/**
 * Finds position of the record with unique ID in vector.
 * 
 * \param x Unique ID of Appointment
 * \return Position of record in vector
 */ 
int ADatabase::find(string x) 
{
	for (int i = 0; i < Visits.size(); i++)
	{
		if (Visits.at(i)->getUniqueAppointmentID() == x)
		{
			return i;
		}
	}
	return -1;
}
/**
 * Displays all Visits, without converting IDs to more plausible form
 * 
 */
void ADatabase::showAll() 
{ 
	cout << "ID wizyty\tID pacjenta\tID doktora\n";
	showAllRecords<Appointment>(Visits); 
}
/**
 * Reads all records from file
 * 
 */
void ADatabase::readAll()
{
	int odczyt_int;
	ifstream source2{ "plik_app.bin", ios::binary };
	while (source2.peek() != std::ifstream::traits_type::eof())
	{
		Visits.push_back(new Appointment);
		Visits.back()->read(source2);
	}
	source2.close();
}
/**
 * Saves all records to file
 * 
 */
void ADatabase::saveAll()
{
	if (NOSAVE == false)
		saveAllRecords(Visits, "plik_app.bin");
	else
		cout << "Opcja zapisywania zostala wylaczona!\n";
	saveAllRecords(Visits, "plik_app.bin");
}
/**
 * Displays visit information.
 * 
 */
void ADatabase::show()
{
	string ID = getString("Unikatowe ID wizyty ktora chcesz odnalezc");
	int y;
	if ((y = this->find(ID)) != -1)
		convertToVisit(y);
	else
		cout << "Nie istnieje wizyta o podanym ID!" << endl;
}

/**
 * This function allows user to convert Visit information from only ID numbers to more understendable form.
 * 
 * \param id Number of index at which visit is in vector
 */
void ADatabase::convertToVisit(int id)
{
	Person* doctor, *patient;
	doctor = base.getPersonOA(base.find(Visits.at(id)->getDoctorid()));
	patient = base.getPersonOA(base.find(Visits.at(id)->getPatientid()));
	cout << "Informacje o wizycie o ID: " << Visits.at(id)->getUniqueAppointmentID() << endl;
	cout << "Lekarz: "; doctor->info();
	cout << "Pacjent: "; patient->info();
}

/**
 * This function is used when particular Doctor was deleted, and we want
 * to mark this in appointment to which he was assigned.
 * 
 * \param ID UNIQUE ID of deleted Doctor
 */
void ADatabase::markDoctor(string ID)
{
	for (int i = 0; i < Visits.size(); i++)
	{
		if (Visits.at(i)->getDoctorid() == ID)
			Visits.at(i)->setDoctorid("DOKTOR USUNIETY");
	}
}
