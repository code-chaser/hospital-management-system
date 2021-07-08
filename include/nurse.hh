#ifndef NURSE
#define NURSE
using namespace std;
#include <string>

#include "./person.hh"

class nurse : public person
{
private:
    string type;

public:
    nurse();
    void fillMap();
    void saveMap();
    void addPerson();
    void printDetails();
    void printDetailsFromHistory(string extraDetails = "");
    void getDetails(int rec = 0);
    void getDetailsFromHistory();
    void removePerson();
};
#endif // !NURSE