#ifndef DOCTOR
#define DOCTOR
using namespace std;
#include <vector>
#include <string>
#include "./person.hh"

class appointment;
class doctor : public person
{
private:
    string type;
    int appointmentsBooked;
    friend class appointment;
    friend class hospital;

public:
    doctor();
    void addPerson();
    void printDetails();
    void printDetailsFromHistory(string extraDetails = "");
    void getDetails(int rec = 0);
    void getDetailsFromHistory();
    void removePerson();
};
#endif // !DOCTOR