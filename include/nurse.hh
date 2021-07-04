#ifndef NURSE
#define NURSE
using namespace std;
#include <string>
#include "./person.hh"

class nurse : public person
{
protected:
    string type;

public:
    nurse();
    void addPerson();
    void printDetails();
    void printDetailsFromHistory(string extraDetails = "");
    void getDetails(int rec = 0);
    void getDetailsFromHistory();
    void removePerson();
};
#endif // !NURSE