#include "Person.h"

Person::Person(string firstname, string lastname, string pesel, string ID, bool cbs) :
	firstname(firstname), lastname(lastname), pesel(pesel) 
{
	cbs = false;
}
Person::~Person(){}

string Person::getFirstname()
{
	return this->firstname;
}

string Person::getLastname()
{
	return this->lastname;
}

string Person::getPesel()
{
	return this->pesel;
}

void Person::setFirstname(string imie)
{
	this->firstname = imie;
}

void Person::setLastname(string nazwisko)
{
	this->lastname = nazwisko;
}

void Person::setPesel(string pesel)
{
	this->pesel = pesel;
}

void Person::setUniqueFacilityID(string t)
{
	this->uniqueFacilityID = t;
}

string Person::getUniqueFacilityID()
{
	return this->uniqueFacilityID;
}

void Person::setCBS()
{
	this->cbs = true;
}

bool Person::getCBS()
{
	return this->cbs;
}
