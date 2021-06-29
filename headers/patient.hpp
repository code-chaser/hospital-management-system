#ifndef PATIENT
#define PATIENT
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./person.hpp"
class patient : public person
{
private:
    int height; //in cms;
    int weight; //in pounds;
    bool hospitalized = 0;
    bool alive = 1;
    bool discharged = 0;

public:
    patient()
    {
        id = -1;
        cat = "patient";
        category = 2;
    }
    void printDetails()
    {
        if (id == -1)
            return;
        printPersonDetails();
        cout << "Height          : " << height << "\n";
        cout << "Weight          : " << weight << "\n";
        cout << "Was Hospitalized? " << ((hospitalized) ? "Y" : "N") << "\n";
        cout << "Alive?          : " << ((alive) ? "Y" : "N") << "\n";
        cout << "Discharged?     : " << ((discharged) ? "Y" : "N") << "\n";
        return;
    }
    void addAPatient()
    {
        //getting the basic details of patient from the user side;
        setDetails();
        //getting patient specific details;
        cout << "Enter the height of the patient (in cms):\n";
        cin >> height;
        cout << "Enter the weight of the patient (in pounds):\n";
        cin >> weight;
        char tt;
        cout << "Is the patient being hospitalized? (Y = Yes || N = No)\n";
        cin >> tt;
        while (tt != 'Y' && tt != 'N')
            cout << "Y or N?\n", cin >> tt;
        hospitalized = (tt == 'Y');
        //creating a fstream object to read/write from/to files;
        fstream f;
        //opening the file to read it;
        f.open("./data/patients.csv", ios::in);
        //reading the file till the last line to get the id of the last line;
        string temp, idString = "";
        bool entry = 0;
        while (getline(f >> ws, temp))
            entry = 1;
        f.close();
        if (entry)
        {
            stringstream s(temp);
            getline(s, idString, ',');
            id = strToNum(idString) + 1;
        }
        else
            id = 1;
        //creating a record in patients.csv;
        f.open("./data/patients.csv", ios::app);
        f << id << "," << firstName << "," << lastName
          << "," << gender << "," << age << "," << mobNumber << "," << address
          << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
          << ","
          << "Y"
          << ","
          << "N" << endl;
        f.close();

        //creating a record in patientsHistory.csv;
        f.open("./data/patientsHistory.csv", ios::app);
        f << firstName << "," << lastName << "," << gender << "," << age
          << "," << mobNumber << "," << address << "," << height << ","
          << weight << "," << ((hospitalized) ? "Y" : "N")
          << ","
          << "Y"
          << ","
          << "N" << endl;
        f.close();

        cout << "\n"
             << firstName << " " << lastName << " added successfully!\n";
        cout << "Their ID is: " << id << "\n";

        return;
    }
};
#endif // !PATIENT