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

//definition of static members in the global scope;
map<int, doctor> hospital::doctorsList;
map<int, patient> hospital::patientsList;
map<int, nurse> hospital::nursesList;
map<int, driver> hospital::driversList;
map<int, ambulance> hospital::ambulancesList;
map<int, appointment> hospital::appointmentsList;
const int hospital::doctorsLimit = 40;
const int hospital::nursesLimit = 100;
const int hospital::driversLimit = 40;
const int hospital::ambulancesLimit = 40;
const int hospital::appointmentsLimit = 320;