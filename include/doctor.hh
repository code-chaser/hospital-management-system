#ifndef DOCTOR
#define DOCTOR
using namespace std;
#include <string>

#include "./person.hh"

class appointment;
class doctor : public person
{
private:
    string type;
    int appointmentsBooked;
    friend class appointment;

public:
    doctor();
    void fillMap();
    void saveMap();
    void addPerson();
    void printDetails();
    void printDetailsFromHistory(string extraDetails = "");
    void getDetails(int rec = 0);
    void getDetailsFromHistory();
    void removePerson();
};
#endif // !DOCTOR