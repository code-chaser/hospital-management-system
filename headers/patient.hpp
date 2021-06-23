#ifndef PATIENT
#define PATIENT
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./person.hpp"
class patient : private person
{
private:
    int id;

public:
    void addAPatient()
    {
        //getting the basic details of patient from the user side;
        setDetails();
        fstream f;
        f.open("./data/patients.csv", ios::app);
        f << id << "," << firstName << "," << lastName << "," << age << "," << gender << "," << mobNumber << "," << address << endl;
        f.close();
        return;
    }
};
#endif // !PATIENT