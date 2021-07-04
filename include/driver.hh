#ifndef DRIVER
#define DRIVER
using namespace std;
#include <string>
#include "./person.hh"

class ambulance;
class driver : public person
{
protected:
    string licenseNumber;
    bool idle;
    friend class ambulance;

public:
    driver();
    void addPerson();
    void printDetails();
    void printDetailsFromHistory(string extraDetails = "");
    void getDetails(int rec = 0);
    void getDetailsFromHistory();
    void removePerson();
};
#endif // !DRIVER