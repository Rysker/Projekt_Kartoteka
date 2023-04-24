#include "Patient.h"

Patient::Patient(int id, string imie, string nazwisko, string pesel, int age, string number): 
Person(imie,nazwisko,pesel), age(age), phonenumber(number) {}
Patient::~Patient() {}
/**
 * Displays information about Patient
 * 
 */
void Patient::info()
{
    cout << getUniqueFacilityID() << " ";
    cout << getFirstname() << " ";
    cout << getLastname() << " ";
    cout << getPesel() << " ";
    cout << getAge() << " ";
    cout << getPhonenumber() << endl;
}
/**
 * This function reads a information, to one record
 * 
 * \param plik File name
 */
void Patient::read(ifstream& plik)
{
    int string_size;
    int odczyt_int;
    string odczyt_string;

    if (plik.good())
    {
        plik.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        odczyt_string.resize(string_size);
        plik.read(reinterpret_cast<char*>(&odczyt_string[0]), string_size);
        this->setFirstname(odczyt_string);

        plik.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        odczyt_string.resize(string_size);
        plik.read(reinterpret_cast<char*>(&odczyt_string[0]), string_size);
        this->setLastname(odczyt_string);

        plik.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        odczyt_string.resize(string_size);
        plik.read(reinterpret_cast<char*>(&odczyt_string[0]), string_size);
        this->setPesel(odczyt_string);

        plik.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        odczyt_string.resize(string_size);
        plik.read(reinterpret_cast<char*>(&odczyt_string[0]), string_size);
        this->setUniqueFacilityID(odczyt_string);

        plik.read(reinterpret_cast<char*>(&odczyt_int), sizeof(int));
        this->setAge(odczyt_int);

        plik.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        odczyt_string.resize(string_size);
        plik.read(reinterpret_cast<char*>(&odczyt_string[0]), string_size);
        this->setPnumber(odczyt_string);
    }
}
/**
 * This function writes all information about record to the file
 * 
 * \param plik Name of file
 */
void Patient::write(ofstream& plik)
{
    int string_size;
    int odczyt_int;
    int t = this->type();
    string odczyt_string;
    if (plik.good())
    {
        plik.write(reinterpret_cast<char*>(&t), sizeof(string_size));

        string_size = firstname.length();
        plik.write(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        plik.write(reinterpret_cast<char*>(&firstname[0]), string_size);

        string_size = lastname.length();
        plik.write(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        plik.write(reinterpret_cast<char*>(&lastname[0]), string_size);

        string_size = pesel.length();
        plik.write(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        plik.write(reinterpret_cast<char*>(&pesel[0]), string_size);

        string_size = uniqueFacilityID.length();
        plik.write(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        plik.write(reinterpret_cast<char*>(&uniqueFacilityID[0]), string_size);

        plik.write(reinterpret_cast<char*>(&age), sizeof(int));

        string_size = phonenumber.length();
        plik.write(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        plik.write(reinterpret_cast<char*>(&phonenumber[0]), string_size);
    }
}

int Patient::getAge() { return this->age; }
string Patient::getPhonenumber() { return this->phonenumber; }
void Patient::setAge(int age) { this->age = age; }
void Patient::setPnumber(string number) { this->phonenumber = number; }

/**
 * This function allows for editing previously created user.
 * User can skip changes on a given field with ENTER
 * 
 */
void Patient::edit() 
{
    string t;
    int x;
    cout << "ENTER bez podania innego znaku pominie edycje pola\nDane w blednym formacie nie zostana zapisane\n";

    if ((t = getStringEdit("imie pacjenta", 1)) != "")
    {
        this->setFirstname(t);
    }
    if ((t = getStringEdit("nazwisko pacjenta", 1)) != "")
    {
        this->setLastname(t);
    }
    if ((t = getStringEdit("PESEL pacjenta", 0)) != "")
    {
        this->setPesel(t);
    }
    if ((t = getStringEdit("wiek pacjenta", 0)) != "")
    {
        try
        {
            t.substr(t.find_first_of("0123456789"));
            int x = stoi(t, NULL, 10);
            this->setAge(x);
        }
        catch (...)
        {
            cout << "Podano blednie wiek! Zostanie on nie zmieniony!\n";
        }
    }
    if ((t = getStringEdit("numer kontaktowy pacjenta", 0)) != "")
    {
        this->setPnumber(t);
    }
}
/**
 * This function allows user to edit newly created Patient
 * 
 */
void Patient::editNew() 
{
    string t;
    int i = 0;
    this->setFirstname(getString("imie", 1));
    this->setLastname(getString("nazwisko", 1));
    this->setPesel(getString("PESEL", 0));
    this->setAge(getInt("wiek pacjenta"));
    this->setPnumber(getString("telefon kontaktowy pacjenta", 0));
}

int Patient::type()
{
    return 1;
}
