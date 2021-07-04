#ifndef PERSON
#define PERSON
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./address.hh"

class person //abstract class
{
protected:
    int id;
    string firstName, lastName;
    char gender;
    int16_t age;
    string mobNumber;
    address add;
    string cat;
    int category;
    //category: 1:doctor; 2:patient; 3:nurse; 4:driver;

public:
    person();
    void addPerson(int16_t minAge = 0, int16_t maxAge = 1000);
    virtual void printDetails();
    virtual void printDetailsFromHistory();
    virtual void getDetails(int rec = 0) = 0;
    virtual void getDetailsFromHistory() = 0;
    virtual void removePerson() = 0;
};
#endif // !PERSON