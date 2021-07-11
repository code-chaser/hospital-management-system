using namespace std;
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/doctor.hh"
#include "./../include/patient.hh"
#include "./../include/nurse.hh"
#include "./../include/driver.hh"
#include "./../include/ambulance.hh"
#include "./../include/appointment.hh"
#include "./../include/hospital.hh"

//defining already declared static members in the global scope;

map<int, doctor> hospital::doctorsList;
map<int, patient> hospital::patientsList;
map<int, nurse> hospital::nursesList;
map<int, driver> hospital::driversList;
map<int, ambulance> hospital::ambulancesList;
map<int, appointment> hospital::appointmentsList;

const int hospital::doctorsLimit = 30;
const int hospital::nursesLimit = 50;
const int hospital::driversLimit = 30;
const int hospital::ambulancesLimit = 30;
const int hospital::appointmentsLimit = 240; //per day;
// ummm, patients limit, ummm, no!
// appointments limit is kind of a patients limit;
// rest hospitalized patients limit must be equal to;
// number of available rooms, maybe I'll add this;
// feature some other day in the future;
// not feeling like doing it right now!

//defining already declared methods;

void hospital::printDoctors()
{
    for (auto i : doctorsList)
        i.second.printDetails(), cout << "\n";
    return;
}
void hospital::printPatients()
{
    for (auto i : patientsList)
        i.second.printDetails(), cout << "\n";
    return;
}
void hospital::printNurses()
{
    for (auto i : nursesList)
        i.second.printDetails(), cout << "\n";
    return;
}
void hospital::printDrivers()
{
    for (auto i : driversList)
        i.second.printDetails(), cout << "\n";
    return;
}
void hospital::printAmbulances()
{
    for (auto i : ambulancesList)
        i.second.printDetails(), cout << "\n";
    return;
}
void hospital::printAppointments()
{
    for (auto i : appointmentsList)
        i.second.printDetails(), cout << "\n";
    return;
}