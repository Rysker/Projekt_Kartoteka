#include "Doctor.h"

Doctor::Doctor(string imie, string nazwisko, string pesel, string licencja, string specjalizacja)
	:Person(imie, nazwisko, pesel), license_number(licencja), specialization(specjalizacja) {};
Doctor::~Doctor(){}
string Doctor::getLicense()
{
	return this->license_number;
}

string Doctor::getSpecialization()
{
	return this->specialization;
}

void Doctor::setLicense(string licencja)
{
	this->license_number = licencja;
}

void Doctor::setSpecialization(string specjalizacja)
{
	this->specialization = specjalizacja;
}
/**
 * Displays all of the information about record
 * 
 */
void Doctor::info()
{
    cout << getUniqueFacilityID() << " ";
	cout << getFirstname() << " ";
	cout << getLastname() << " ";
	cout << getPesel() << " ";
	cout << getLicense() << " ";
	cout << getSpecialization() << endl;
}
/**
 * This function reads all information about record to the file
 *
 * \param plik Name of file
 */
void Doctor::read(ifstream& plik)
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

        plik.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        odczyt_string.resize(string_size);
        plik.read(reinterpret_cast<char*>(&odczyt_string[0]), string_size);
        this->setLicense(odczyt_string);

        plik.read(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        odczyt_string.resize(string_size);
        plik.read(reinterpret_cast<char*>(&odczyt_string[0]), string_size);
        this->setSpecialization(odczyt_string);
    }
}
/**
 * This function writes all information about record to the file
 *
 * \param plik Name of file
 */
void Doctor::write(ofstream& plik)
{
    int string_size;
    int i = 0;
    if (plik.good())
    {
        plik.write(reinterpret_cast<char*>(&i), sizeof(int));

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

        string_size = license_number.length();
        plik.write(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        plik.write(reinterpret_cast<char*>(&license_number[0]), string_size);

        string_size = specialization.length();
        plik.write(reinterpret_cast<char*>(&string_size), sizeof(string_size));
        plik.write(reinterpret_cast<char*>(&specialization[0]), string_size);
    }
}
/**
 * Function used when we have to edit a Doctor, that was already created.
 * 
 */
void Doctor::edit() 
{
    string t;
    cout << "ENTER bez podania innego znaku pominie edycje pola\nDane w blednym formacie nie zostana zapisane\n";
  
    if ((t = getStringEdit("imie lekarza", 1)) != "")
    {
        this->setFirstname(t);
    }
    if ((t = getStringEdit("nazwisko lekarza", 1)) != "")
    {
        this->setLastname(t);
    }
    if ((t = getStringEdit("PESEL lekarza", 0)) != "")
    {
        this->setPesel(t);
    }
    if ((t = getStringEdit("licencje lekarza")) != "")
    {
        this->setLicense(t);
    }
    if ((t = getStringEdit("specjalizacje lekarza", 1)) != "")
    {
        this->setSpecialization(t);
    }
}
/**
 * Informs if given record is a Doctor. Necessary in some functions.
 * 
 * \return Returns 0
 */
int Doctor::type()
{
    return 0;
}
/**
 * This function is invoked when new Doctor is created. It allows user to 
 * write information about freshly created record.
 * 
 */
void Doctor::editNew() 
{
    string t;
    int i = 0;
    this->setFirstname(getString("imie", 1));
    this->setLastname(getString("nazwisko", 1));
    this->setPesel(getString("PESEL", 0));
    this->setLicense(getString("licencje"));
    this->setSpecialization(getString("specjalizacje", 1));
}
