#ifndef DRIVER
#define DRIVER
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./person.hpp"
class ambulance;
class driver : public person
{
protected:
    string licenseNumber = "";
    ambulance* A;
    bool free=1;

public:
    driver()
    {
        id = -1;
        cat = "driver";
        category = 4;
    }
    void addADriver()
    {
    }
    void getADriver()
    {
    }
};
#endif // !DRIVER