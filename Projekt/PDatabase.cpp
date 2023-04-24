#include "PDatabase.h"
#include "ADatabase.h"

extern bool NOSAVE;
extern bool NOEDIT;
extern ADatabase base_app;

/**
 * This template allows for saving all records from given vector
 * 
 * \param v Vector with pointers to objects
 * \param source File name
 */
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
	while(v.size() != 0)
	{
		v.back()->write(source3);
		v.pop_back();
	}
	source3.close();
}

template <typename T> bool greater2(T a, T b)
{
	return a > b;
}

template <typename T> bool lower2(T a, T b)
{
	return a < b;
}

template <typename T> bool equal(T a, T b)
{
	return a == b;
}

PDatabase::PDatabase() {}
PDatabase::~PDatabase() {}
vector<Person*>* PDatabase::getBase() { return &(this->PersonsBase); }
/**
 * This function sorts Persons by theri unique ID
 * 
 * \param x In which order ID is sorted (1 or -1 /ascending or descending)
 */
void PDatabase::sort(int x)
{
	int i;
	do
	{
		i = 0;
		for (int j = 0; j < this->PersonsBase.size() - 1; j++)
		{
			if (x > 0)
			{
				if (greater2(this->PersonsBase[j]->getUniqueFacilityID(), this->PersonsBase[j + 1]->getUniqueFacilityID()))
				{
					swap(this->PersonsBase[j], this->PersonsBase[j + 1]);
					i++;
				}
			}

			if (x < 0)
			{
				if (lower2(this->PersonsBase[j]->getUniqueFacilityID(), this->PersonsBase[j + 1]->getUniqueFacilityID()))
				{
					swap(this->PersonsBase[j], this->PersonsBase[j + 1]);
					i++;
				}
			}
		}
	} while (i != 0);
}
/**
 * This function sorts Persons by their first name and then last name respectively
 * Each call of this function will change order of sorting
 * 
 * \param x In which order first name is sorted (1 or -1 /ascending or descending)
 * \param y In which order last name is sorted (1 or -1 /ascending or descending)
 */
void PDatabase::sort(int x, int y)
{
	int i;
	do
	{
		i = 0;
		for (int j = 0; j < this->PersonsBase.size() - 1; j++)
		{
			if (x > 0)
			{
				if (greater2(this->PersonsBase[j]->getFirstname(), this->PersonsBase[j + 1]->getFirstname()))
				{
					swap(this->PersonsBase[j], this->PersonsBase[j + 1]);
					i++;
				}
				else if (equal(this->PersonsBase[j]->getFirstname(), this->PersonsBase[j + 1]->getFirstname()) && greater2(this->PersonsBase[j]->getLastname(), this->PersonsBase[j + 1]->getLastname()))
				{
					swap(this->PersonsBase[j], this->PersonsBase[j + 1]);
					i++;
				}
			}

			if (x < 0)
			{
				if (lower2(this->PersonsBase[j]->getFirstname(), this->PersonsBase[j + 1]->getFirstname()))
				{
					swap(this->PersonsBase[j], this->PersonsBase[j + 1]);
					i++;
				}
				else if (equal(this->PersonsBase[j]->getFirstname(), this->PersonsBase[j + 1]->getFirstname()) && lower2(this->PersonsBase[j]->getLastname(), this->PersonsBase[j + 1]->getLastname()))
				{
					swap(this->PersonsBase[j], this->PersonsBase[j + 1]);
					i++;
				}
			}
		}
	} while (i != 0);
}
/**
 * This function shows all Patients or Doctors
 * 
 * \param x This parameter changes if Patients or Doctors will be displayed
 */
void PDatabase::showAll(int x)
{
	if (this->PersonsBase.size() == 0)
		return;
	if (x == 0)
	{
		cout << "ID Doktora|Imie|Nazwisko|PESEL|Licencja|Specjalizacja\n";
		for (int i = 0; i <= this->PersonsBase.size() - 1; i++)
		{
			if (this->PersonsBase[i]->type() == 0)
			{
				this->PersonsBase[i]->info();
			}
		}
	}

	if (x == 1)
	{
		cout << "ID Pacjenta|Imie|Nazwisko|PESEL|Wiek|Numer telefonu\n";
		for (int i = 0; i <= this->PersonsBase.size() - 1; i++)
		{
			if (this->PersonsBase[i]->type() == 1)
			{
				this->PersonsBase[i]->info();
			}
		}
	}

}
/**
 * This function allows user to display information about given Person.
 * 
 * \param x 1-User has to be Patient, 0-User has to be Doctor
 */
void PDatabase::show(int x)
{
	string z = getString("ID osoby ktora chcesz odnalezc");
	int y;
	if ((y = this->find(z)) != -1)
	{
		if (PersonsBase.at(y)->type() != x)
			cout << "Osoba o podanym ID nie jest lekarzem/pacjentem!" << endl;
		else PersonsBase.at(y)->info();
	}
	else
		cout << "Nie istnieje osoba podanym ID!" << endl;
}
/**
 * This function handles adding the new Doctor to the base.
 * 
 */
void PDatabase::addDoctor()
{
	string t;
	try
	{
		PersonsBase.push_back(new Doctor);
	}
	catch (bad_alloc& err)
	{
		cout << "Blad new\n";
		return;
	}
	PersonsBase.back()->editNew();
	do
	{
		t = generateUniqueID('D');
		
	} while (find(t) != -1 && PersonsBase.size() != 0);
	PersonsBase.back()->setUniqueFacilityID(t);
	PersonsBase.back()->setCBS();
	saveAll();
}
/**
 * This function handles adding the new Patient to the base.
 * 
 */
void PDatabase::addPatient()
{
	string t;
	try
	{
		PersonsBase.push_back(new Patient);
	}
	catch (bad_alloc& err)
	{
		cout << "Blad new\n";
		return;
	}

	PersonsBase.back()->editNew();
	do
	{
		t = generateUniqueID('P');

	} while (find(t) != -1);
	PersonsBase.back()->setUniqueFacilityID(t);
	PersonsBase.back()->setCBS();
	saveAll();
}
/**
 * This function checks if user can edit the records. If yes then it asks user for
 * input, invokes correct methods from Person derived classes and saves results if no 
 * errors happen.
 * 
 */
void PDatabase::editPerson()
{
	if (NOEDIT == false)
	{
		string x = getString("ID osoby ktora chcesz edytowac");
		int y;
		if ((y = this->find(x)) != -1)
		{
			cout << "Informacje o osobie ktora chcesz edytowac:\n";
			PersonsBase.at(y)->info();
			PersonsBase.at(y)->edit();
		}
		else
			cout << "Nie istnieje osoba o podanym ID!" << endl;
		saveAll();
	}
	else
		cout << "Mozliwosc edycji zostala wylaczona\n";
}
/**
 * This function finds a position of object in vector
 * 
 * \param x Unique ID used to identify correct record
 * \return On success returns index of vector at which is object, otherwise returns -1
 * to inform about failure
 */
int PDatabase::find(string x)
{
	string t;
	for (int i = 0; i < PersonsBase.size(); i++)
	{
		try
		{
			t = PersonsBase.at(i)->getUniqueFacilityID();
		}
		catch (out_of_range &err)
		{
			cout << "Blad wektora w funkcji find";
			return -1;
		}
		if (PersonsBase.at(i)->getUniqueFacilityID() == x)
			return i;
	}
	return -1;
}
/**
 * This function removes a record from vector.
 * It asks a user of ID of record. If such a record exists it deletes it. It also
 * changes or deletes appointment according to the rule"
 * If Patient is deleted, then delete Appointment, if Doctor then inform about it in appointment
 * 
 */
void PDatabase::removePerson()
{
	string x = getString("ID wizyty ktora chcesz usunac");
	int y;
	if ((y = this->find(x)) != -1)
	{
		string ID = (string)PersonsBase.at(y)->getUniqueFacilityID();
		int type = PersonsBase.at(y)->type();

		delete PersonsBase.at(y);
		PersonsBase.erase(PersonsBase.begin() + y);

		if (type == 1)
			base_app.removeAppointment(ID);
		if (type == 0)
		{
			base_app.markDoctor(ID);
		}
			
	}
	else
		cout << "Nie istnieje wizyta o podanym ID!" << endl;
}
/**
	This function reads all records from file
 
 */
void PDatabase::readAll() 
{
	int odczyt_int;
	ifstream source2{ "plik.bin", ios::binary };
	while (source2.peek() != std::ifstream::traits_type::eof())
	{
		source2.read(reinterpret_cast<char*>(&odczyt_int), sizeof(int));
		if (odczyt_int < 0)
			break;
		if (odczyt_int == 1)
		{
			PersonsBase.push_back(new Patient);
			PersonsBase.back()->read(source2);
		}
		if (odczyt_int == 0)
		{
			PersonsBase.push_back(new Doctor);
			PersonsBase.back()->read(source2);
		}
	}
	source2.close();
}
/**
  This function saves all objects currently held in Vector<PersonsBase*> by
  using template function saveAllRecords.
 *
 */
void PDatabase::saveAll() 
{
	if (NOSAVE == false)
		saveAllRecords(PersonsBase, "plik.bin");
	else
		cout << "Opcja zapisywania zostala wylaczona!\n";
}

/**
 * This function returns address of the object at given location in vector.
 * 
 * \param x Location of object in vector
 * \return Returns address of object, from given vector index
 */
Person* PDatabase::getPersonOA(int x)
{
	try
	{
		return PersonsBase.at(x);
	}
	catch(out_of_range& err)
	{
		cout << "Blad w uzyskaniu dostepu do indeksu wektora!\n";
		exit(1);
	}
}
