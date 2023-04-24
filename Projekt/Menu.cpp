#include "Person.h"
#include "Menu.h"
#include "PDatabase.h"
#include "Appointment.h"
#include "ADatabase.h"

template<class T>
void purge(vector<T*> v)
{
	for (auto item : v)
		delete item;
	v.clear();
}

extern PDatabase base;
extern ADatabase base_app;
/**
 * Main menu of the program
 * 
 */
void start()
{
	cls();
	int wybor;
	cout << "Menu glowne kartoteki" << endl;
	cout << "1- Wyswietl liste lekarzy, pacjentow lub wizyt" << endl;
	cout << "2- Dodaj/Usun/Edytuj wizyty" << endl;
	cout << "3- Dodaj/Usun/Edytuj lekarzy i pacjentow" << endl;
	cout << "4- Wyjscie" << endl;
	wybor = getInt("wybor");
	wyborstart(wybor);
}

void wyborstart(int wybor)
{
	cls();
	if (wybor == 1)
		lista();
	if (wybor == 2)
		wizyty();
	if (wybor == 3)
		pledycja();
	else
		koniec();
	
}
/**
 * One of the submenus. It allows to display all bases, pick particular record, and allows to 
 * sort Persons base.
 * 
 */
void lista()
{
	static int x3 = -1;
	static int x4 = -1;
	int wybor;
	cout << "Menu listy lekarzy i pacjentow" << endl;
	cout << "1- Wyswietl liste lekarzy" << endl;
	cout << "2- Wyswietl liste pacjentow" << endl;
	cout << "3- Wyswietl liste wizyt" << endl;
	cout << "4- Znajdz wybranego lekarza" << endl;
	cout << "5- Znajdz wybranego pacjenta" << endl;
	cout << "6- Znajdz wybrana wizyte" << endl;
	cout << "7- Posortuj liste lekarzy i pacjetow wg indeksu (wybranie opcji kolejny raz zmieni kolejnosc sortowania)" << endl;
	cout << "8- Posortuj liste lekarzy i pacjetow wg imienia i nazwiska (wybranie opcji kolejny raz zmieni kolejnosc sortowania)" << endl;
	cout << "9- Wstecz" << endl;
	wybor = getInt("wybor");
	cls();
	if (wybor == 1)
	{
		base.showAll(0);
		lista();
	}

	if (wybor == 2)
	{

		base.showAll(1);
		lista();
	}

	if (wybor == 3)
	{
		base_app.showAll();
		lista();
	}

	if (wybor == 4)
	{
		base.show(0);
		lista();
	}

	if (wybor == 5)
	{
		base.show(1);
		lista();
	}

	if (wybor == 6)
	{
		base_app.show();
		lista();
	}

	if (wybor == 7)
	{
		x3 *= -1;
		base.sort(x3);
		lista();
	}

	if (wybor == 8)
	{
		x4 *= -1;
		base.sort(x4, x4);
		lista();
	}

	if (wybor == 9) start();
}
/**
 * One of the submenus. It handles modifying/deleting and adding of Appointments
 *
 */
void wizyty()
{
	
	int wybor;
	cout << "Menu listy lekarzy i pacjentow" << endl;
	cout << "1- Dodaj wizyte" << endl;
	cout << "2- Edytuj wizyte" << endl;
	cout << "3- Usun wizyte" << endl;
	cout << "4- Wstecz" << endl;
	wybor = getInt("wybor");
	cls();
	if (wybor == 1) 
	{ 
		base_app.addAppointment();
		wizyty(); 
	}

	if (wybor == 2)
	{ 
		base_app.editAppointment();
		wizyty();
	}

	if (wybor == 3) 
	{ 
		base_app.removeAppointment(); 
		wizyty();
	}
	if (wybor == 4) { start(); }
	
}
/**
 * One of the submenus. It handles modifying/deleting and adding of Persons
 * 
 */
void pledycja()
{
	int wybor;
	cout << "Menu listy lekarzy i pacjentow" << endl;
	cout << "1- Dodaj lekarza" << endl;
	cout << "2- Dodaj pacjenta" << endl;
	cout << "3- Edytuj osobe o wybranym id" << endl;
	cout << "4- Usun osobe o wybranym id" << endl;
	cout << "5- Wstecz" << endl;
	wybor = getInt("wybor");
	cls();
	if (wybor == 1)
	{
		base.addDoctor();
		pledycja();
	}
	if (wybor == 2)
	{
		base.addPatient();
		pledycja();
	}
	if (wybor == 3)
	{
		base.editPerson();
		pledycja();
	}

	if (wybor == 4)
	{
		base.removePerson();
		pledycja();
	}

	if (wybor == 5) start();
}
/**
 * Invoked on the end. Saves all records from all bases.
 * 
 */
void koniec()
{
	base.saveAll();
	base_app.saveAll();
}
