#ifndef APPOINTMENT
#define APPOINTMENT
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./patient.hpp"
#include "./doctor.hpp"
class appointment
{
private:
    doctor* D;
    patient* P;
    int hh, mm; //hh -> hour in 24 hour format; mm -> minutes;
public:
    appointment()
    {
    }
    void book()
    {
        cout<<"Is the patient already registered?";
    }
};
#endif // !APPOINTMENT