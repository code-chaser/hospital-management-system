#ifndef APPOINTMENT
#define APPOINTMENT
using namespace std;
#include <vector>

#include "./patient.hh"
#include "./doctor.hh"

class appointment
{
private:
    int id;
    doctor D;
    patient P;
    int hh; //hh -> hour in 24 hour format;
public:
    appointment();
    ~appointment();
    void printDetails();
    void book();
    void fillDetails();
    void getDetails();
    void printAll();
};
#endif // !APPOINTMENT