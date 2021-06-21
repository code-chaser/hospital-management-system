#ifndef PATIENT
#define PATIENT
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "./../person.cpp"
class patient : private person
{
private:
    int patientId;

public:
    void addAPatient()
    {
        cout << "\nEnter the name of the patient: \nFirst Name:\n";
        getline(cin >> ws, firstName);
        cout << "\nLast name:\n";
        getline(cin >> ws, lastName);
        cout << "\nEnter the age of the patient: \n";
        cin >> age;
        while (age <= 0)
            cout << "Was that supposed to make any kind of sense?\nEnter again!\n", cin >> age;
        cout << "\nEnter the gender of the patient (M = Male || F = Female): \n";
        cin >> gender;
        while (gender != 'M' && gender != 'F')
            cout << "M or F?\n", cin >> gender;
        fstream f;
        f.open("./doctors/doctors.csv", ios::app);
        f << firstName << "," << lastName << "," << age << "," << gender << endl;
        f.close();
        return;
    }
};
#endif // !PATIENT