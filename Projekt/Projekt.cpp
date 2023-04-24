#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
#include "Menu.h"
#include "PDatabase.h"
#include "ADatabase.h"

using namespace std;

/**
 * If false then user can save data, otherwise he can not.
 */
bool NOSAVE = false;
/**
 * If false user can edit ALREADY EXISTING objects, otherwise he can not.
 * No matter the option user can always create new objects.
 */
bool NOEDIT = false;
PDatabase base;
ADatabase base_app;

int main(int argc, char* argv[])
{
    bool exit = checkParameters(argc, argv);
    if (exit == false)
    {
        return 0;
    }

    base.readAll();
    base_app.readAll();
    srand(time(NULL));
    //(*(base.getBase()))[0]->info();
    //(*(base.getBase()))[1]->info();
    //(*(base.getBase()))[2]->info();
    //(*(base.getBase()))[3]->info();
    start();
    //cout << (PersonsBase[1] == PersonsBase[2]);
  
    return 0;
}