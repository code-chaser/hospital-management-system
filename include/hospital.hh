#ifndef HOSPITAL
#define HOSPITAL
using namespace std;
#include <string>
#include <vector>
#include <map>
#include "global.hh"
#include "doctor.hh"
#include "patient.hh"
#include "nurse.hh"
#include "driver.hh"
#include "ambulance.hh"
#include "appointment.hh"

class hospital
{
private:
    map<int, doctor> doctors;
    map<int, patient> patients;
    map<int, nurse> nurses;
    map<int, driver> drivers;
    map<int, ambulance> ambulances;
    map<int, appointment> appointments;
    int doctorsLimit;
    int nursesLimit;
    int driversLimit;
    int ambulancesLimit;
    int appointmentsLimit;
public:
    hospital();
};

#endif // !HOSPITAL