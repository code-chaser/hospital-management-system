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
protected:
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
        cout << "\nEnter the height of the patient (in cms):\n";
        cin >> height;
        cout << "\nEnter the weight of the patient (in pounds):\n";
        cin >> weight;
        char tt;
        cout << "\nIs the patient being hospitalized? (Y = Yes || N = No)\n";
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
    void getAPatient()
    {
        int opt = 0;
        cout << "\nOPTIONS:\n[1]: Filter by ID\n[2]: Filter by name\n\n";
        cin >> opt;
        while (opt != 1 && opt != 2)
            cout << "option 1 or 2?\n", cin >> opt;
        //1: Filter by ID;
        if (opt == 1)
        {
            int reqId;
            cout << "\nEnter ID:\n";
            cin >> reqId;

            fstream f;
            f.open("./data/patients.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s1, s4, s5, s8, s9, s10, s11, s12;
                //reading from the string stream object 's';
                getline(s, s1, ',');

                if (reqId == strToNum(s1))
                {
                    getline(s, firstName, ',');
                    getline(s, lastName, ',');
                    getline(s, s4, ',');
                    getline(s, s5, ',');
                    getline(s, mobNumber, ',');
                    getline(s, address, ',');
                    getline(s, s8, ',');
                    getline(s, s9, ',');
                    getline(s, s10, ',');
                    getline(s, s11, ',');
                    getline(s, s12, ',');
                    id = reqId;
                    gender = s4[0];
                    age = strToNum(s5);
                    height = strToNum(s8);
                    weight = strToNum(s9);
                    hospitalized = s10[0] - '0';
                    alive = s11[0] - '0';
                    discharged = s12[0] - '0';
                    return;
                }
            }
            f.close();
            //if a record is found, it's details will be stored in the doctor class object that called this function,
            //and the control is returned;
            //else:
            cout << "\nNo matching record found!\n";
            return;
        }
        //2: Filter by name;
        else if (opt == 2)
        {
            string reqFName, reqLName;
            cout << "First Name:\n";
            getline(cin >> ws, reqFName);
            cout << "\nLast Name:\n";
            getline(cin >> ws, reqLName);
            vector<patient> matchingRecords;
            fstream f;
            f.open("./data/patients.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                patient p;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s1, s4, s5, s8, s9, s10, s11, s12;
                //reading from the string stream object 's';
                getline(s, s1, ',');
                getline(s, p.firstName, ',');
                getline(s, p.lastName, ',');

                if (p.firstName == reqFName && p.lastName == reqLName)
                {
                    getline(s, s4, ',');
                    getline(s, s5, ',');
                    getline(s, p.mobNumber, ',');
                    getline(s, p.address, ',');
                    getline(s, s8, ',');
                    getline(s, s9, ',');
                    getline(s, s10, ',');
                    getline(s, s11, ',');
                    getline(s, s12, ',');
                    p.id = strToNum(s1);
                    p.gender = s4[0];
                    p.age = strToNum(s5);
                    p.height = strToNum(s8);
                    p.weight = strToNum(s9);
                    p.hospitalized = s10[0] - '0';
                    p.alive = s11[0] - '0';
                    p.discharged = s12[0] - '0';
                    matchingRecords.push_back(p);
                }
            }
            f.close();
            cout << "\n";
            cout << matchingRecords.size() << " matching record(s) found!\n";
            for (auto i : matchingRecords)
                i.printDetails();
            char tt = 'N';
            if (matchingRecords.size() > 1)
            {
                do
                {
                    int reqId;
                    cout << "\nEnter the ID of the required patient: ";
                    cin >> reqId;
                    for (auto i : matchingRecords)
                        if (reqId == i.id)
                        {
                            id = i.id;
                            firstName = i.firstName;
                            lastName = i.lastName;
                            gender = i.gender;
                            age = i.age;
                            mobNumber = i.mobNumber;
                            address = i.address;
                            height = i.height;
                            weight = i.weight;
                            hospitalized = i.hospitalized;
                            alive = i.alive;
                            discharged = i.discharged;
                            return;
                        }
                    cout << "\nInvalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> tt;
                    while (tt != 'Y' || tt != 'N')
                        cout << "Y or N?\n", cin >> tt;
                } while (tt == 'Y');
            }
        }
        return;
    }
    
};
#endif // !PATIENT