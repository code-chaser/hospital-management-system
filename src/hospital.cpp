using namespace std;
#include <iostream>
#include <sstream>
#include <fstream>
#include "./../include/hospital.hh"

hospital::hospital()
{
    fstream f;
    f.open("./data/doctors.csv");
}