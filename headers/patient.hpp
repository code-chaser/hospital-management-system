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

public:
    patient()
    {
        id = -1;
        cat = "patient";
        category = 2;
    }
    void addPerson()
    {
        //getting the basic details of patient from the user side;
        person::addPerson();
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
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
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
          << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
          << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
          << ","
          << "Y"
          << "\n";
        f.close();

        //creating a record in patientsHistory.csv;
        f.open("./data/patientsHistory.csv", ios::app);
        f << firstName << "," << lastName << "," << gender << "," << age
          << "," << mobNumber << "," << add.addToStr() << "," << height << ","
          << weight << "," << ((hospitalized) ? "Y" : "N")
          << ","
          << "Y"
          << ","
          << "N"
          << "\n";
        f.close();

        cout << "\n"
             << firstName << " " << lastName << " added successfully!\n";
        cout << "Their ID is: " << id << "\n";

        return;
    }
    void printDetails()
    {
        if (id == -1)
            return;
        person::printDetails();
        cout << "Height (cms)    : " << height << "\n";
        cout << "Weight (pounds) : " << weight << "\n";
        cout << "Was Hospitalized? " << ((hospitalized) ? "Y" : "N") << "\n";
        cout << "Alive?          : " << ((alive) ? "Y" : "N") << "\n";
        return;
    }
    void printDetailsFromHistory(string extraDetails = "")
    {
        if (id == -1)
            return;
        person::printDetailsFromHistory();
        stringstream k(extraDetails);
        string s1;
        getline(k, s1, ',');
        if (extraDetails == "")
        {
            fstream f;
            f.open("./data/patientsHistory.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                patient p;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s3, s4, s6, s7, s8, s9, s10;
                //reading from the string stream object 's';
                getline(s, p.firstName, ',');
                getline(s, p.lastName, ',');
                getline(s, s3, ',');
                getline(s, s4, ',');
                getline(s, p.mobNumber, ',');

                if (p.firstName == firstName && p.lastName == lastName && p.mobNumber == mobNumber)
                {

                    getline(s, s6, ',');
                    getline(s, s7, ',');
                    getline(s, s8, ',');
                    getline(s, s9, ',');
                    getline(s, s10, ',');
                    getline(s, s1, ',');
                }
            }
            f.close();
        }
        cout << "Height (cms)    : " << height << "\n";
        cout << "Weight (pounds) : " << weight << "\n";
        cout << "Was Hospitalized? " << ((hospitalized) ? "Y" : "N") << "\n";
        cout << "Alive?          : " << ((alive) ? "Y" : "N") << "\n";
        cout << "Discharged?     : " << s1 << "\n";
        return;
    }
    void getDetails()
    {
        int opt = 0;
        cout << "\nOPTIONS:\n[1]: Filter by ID\n[2]: Filter by Name\n\n";
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
                string s1, s4, s5, s7, s8, s9, s10, s11;
                //reading from the string stream object 's';
                getline(s, s1, ',');

                if (reqId == strToNum(s1))
                {
                    getline(s, firstName, ',');
                    getline(s, lastName, ',');
                    getline(s, s4, ',');
                    getline(s, s5, ',');
                    getline(s, mobNumber, ',');
                    getline(s, s7, ',');
                    getline(s, s8, ',');
                    getline(s, s9, ',');
                    getline(s, s10, ',');
                    getline(s, s11, ',');
                    id = reqId;
                    gender = s4[0];
                    age = strToNum(s5);
                    add.strToAdd(s7);
                    height = strToNum(s8);
                    weight = strToNum(s9);
                    hospitalized = (s10 == "Y");
                    alive = (s11 == "Y");
                    return;
                }
            }
            f.close();
            //if a record is found, it's details will be stored in the patient class object that called this function,
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
            getline(cin, reqLName);
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
                string s1, s4, s5, s7, s8, s9, s10, s11;
                //reading from the string stream object 's';
                getline(s, s1, ',');
                getline(s, p.firstName, ',');
                getline(s, p.lastName, ',');

                if (p.firstName == reqFName && p.lastName == reqLName)
                {
                    getline(s, s4, ',');
                    getline(s, s5, ',');
                    getline(s, p.mobNumber, ',');
                    getline(s, s7, ',');
                    getline(s, s8, ',');
                    getline(s, s9, ',');
                    getline(s, s10, ',');
                    getline(s, s11, ',');
                    p.id = strToNum(s1);
                    p.gender = s4[0];
                    p.age = strToNum(s5);
                    add.strToAdd(s7);
                    p.height = strToNum(s8);
                    p.weight = strToNum(s9);
                    hospitalized = (s10 == "Y");
                    alive = (s11 == "Y");
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
                            add = i.add;
                            height = i.height;
                            weight = i.weight;
                            hospitalized = i.hospitalized;
                            alive = i.alive;
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
    void getDetailsFromHistory()
    {
        int opt = 0;
        cout << "\nOPTIONS:\n[1]: Filter by Name\n[2]: Filter by Mobile Number\n\n";
        cin >> opt;
        while (opt != 1 && opt != 2)
            cout << "option 1 or 2?\n", cin >> opt;
        //1: Filter by name;
        if (opt == 1)
        {
            string reqFName, reqLName;
            cout << "First Name:\n";
            getline(cin >> ws, reqFName);
            cout << "\nLast Name:\n";
            getline(cin, reqLName);
            vector<patient> matchingRecords;
            vector<string> extraDetails;
            fstream f;
            f.open("./data/patientsHistory.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                patient p;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s3, s4, s6, s7, s8, s9, s10, s12;
                //reading from the string stream object 's';
                getline(s, p.firstName, ',');
                getline(s, p.lastName, ',');

                if (p.firstName == reqFName && p.lastName == reqLName)
                {
                    getline(s, s3, ',');
                    getline(s, s4, ',');
                    getline(s, p.mobNumber, ',');
                    getline(s, s6, ',');
                    getline(s, s7, ',');
                    getline(s, s8, ',');
                    getline(s, s9, ',');
                    getline(s, s10, ',');
                    getline(s, s10, ',');
                    getline(s, s12);
                    p.id = 0;
                    p.gender = s3[0];
                    p.age = strToNum(s4);
                    add.strToAdd(s6);
                    p.height = strToNum(s7);
                    p.weight = strToNum(s8);
                    hospitalized = (s9 == "Y");
                    alive = (s10 == "Y");
                    matchingRecords.push_back(p);
                    extraDetails.push_back(s12);
                }
            }
            f.close();
            cout << "\n";
            cout << matchingRecords.size() << " matching record(s) found!\n";
            for (int i = 0; i < matchingRecords.size(); i++)
                matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
        }
        //2: Filter by mobNumber;
        else if (opt == 2)
        {
            string reqMobNum;
            cout << "Enter mobile number:\n";
            cin >> reqMobNum;
            vector<patient> matchingRecords;
            vector<string> extraDetails;
            fstream f;
            f.open("./data/patientsHistory.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                patient p;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s3, s4, s6, s7, s8, s9, s10, s12;
                //reading from the string stream object 's';
                getline(s, p.firstName, ',');
                getline(s, p.lastName, ',');
                getline(s, s3, ',');
                getline(s, s4, ',');
                getline(s, p.mobNumber, ',');

                if (reqMobNum == p.mobNumber)
                {
                    getline(s, s6, ',');
                    getline(s, s7, ',');
                    getline(s, s8, ',');
                    getline(s, s9, ',');
                    getline(s, s10, ',');
                    getline(s, s12);
                    p.id = 0;
                    p.gender = s3[0];
                    p.age = strToNum(s4);
                    add.strToAdd(s6);
                    p.height = strToNum(s7);
                    p.weight = strToNum(s8);
                    hospitalized = (s9 == "Y");
                    alive = (s10 == "Y");
                    matchingRecords.push_back(p);
                    extraDetails.push_back(s12);
                }
            }
            f.close();
            cout << "\n";
            cout << matchingRecords.size() << " matching record(s) found!\n";
            for (int i = 0; i < matchingRecords.size(); i++)
                matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
        }
        return;
    }
    void hospitalize()
    {
        cout << "\nSearch for the patient.\n";
        getDetails();
        string s, temp, corrected;
        stringstream str;
        str << id << "," << firstName << "," << lastName
            << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
            << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
            << ","
            << ((alive) ? "Y" : "N") << "\n";
        getline(str >> ws, s);
        str << id << "," << firstName << "," << lastName
            << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
            << "," << height << "," << weight << ","
            << "Y"
            << ","
            << ((alive) ? "Y" : "N") << "\n";
        getline(str >> ws, corrected);
        fstream f, fout("./data/temp.csv", ios::out);
        f.open("./data/patients.csv", ios::in);
        while (getline(f, temp))
        {
            if (temp != s)
                fout << temp << "\n";
            else
                fout << corrected << "\n";
        }
        f.close();
        fout.close();
        s.erase();
        temp.erase();
        remove("./data/patients.csv");
        rename("./data/temp.csv", "./data/patients.csv");
        str << firstName << "," << lastName
            << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
            << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
            << ","
            << ((alive) ? "Y" : "N")
            << ",N"
            << "\n";
        getline(str >> ws, s);
        str << firstName << "," << lastName
            << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
            << "," << height << "," << weight << ","
            << "Y,"
            << ((alive) ? "Y,N\n" : "N,N\n");
        getline(str >> ws, corrected);
        f.open("./data/patientsHistory.csv", ios::in);
        fout.open("./data/temp.csv", ios::out);
        while (getline(f, temp))
        {
            if (temp == s)
                fout << corrected << "\n";
            else
                fout << temp << "\n";
        }
        f.close();
        fout.close();
        s.erase();
        temp.erase();
        remove("./data/patientsHistory.csv");
        rename("./data/temp.csv", "./data/patientsHistory.csv");
        cout << firstName << " " << lastName << " hospitalized successfully!\n";
        return;
    }
    void reportADeath()
    {
        cout << "\nSearch for the patient.\n";
        getDetails();
        string s, temp, corrected;
        stringstream str(s);
        str << id << "," << firstName << "," << lastName
            << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
            << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
            << ","
            << ((alive) ? "Y" : "N") << "\n";
        getline(str, s);
        str << id << "," << firstName << "," << lastName
            << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
            << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
            << ","
            << "N"
            << "\n";
        getline(str, corrected);
        fstream f, fout("./data/temp.csv", ios::out);
        f.open("./data/patients.csv", ios::in);
        while (getline(f, temp))
        {
            if (temp != s)
                fout << temp << "\n";
            else
                fout << corrected << "\n";
        }
        f.close();
        fout.close();
        s.erase();
        temp.erase();
        remove("./data/patients.csv");
        rename("./data/temp.csv", "./data/patients.csv");
        str << firstName << "," << lastName
            << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
            << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
            << ","
            << ((alive) ? "Y" : "N")
            << ",N"
            << "\n";
        getline(str, s);
        f.open("./data/patientsHistory.csv", ios::in);
        fout.open("./data/temp.csv", ios::out);
        while (getline(f, temp))
        {
            if (temp == s)
            {
                fout << firstName << "," << lastName
                     << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
                     << "," << height << "," << weight << "," << ((hospitalized) ? "Y,N,N\n" : "N,N,N\n");
            }
            else
                fout << temp << "\n";
        }
        f.close();
        fout.close();
        s.erase();
        temp.erase();
        remove("./data/patientsHistory.csv");
        rename("./data/temp.csv", "./data/patientsHistory.csv");
        cout << firstName << " " << lastName << " reported dead, we hope their soul rests in peace, amen!\n";
        return;
    }
    void removePerson()
    {
        cout << "\nSearch for the patient you want to remove.\n";
        getDetails();
        string s, temp;
        stringstream str(s);
        str << id << "," << firstName << "," << lastName
            << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
            << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
            << ","
            << ((alive) ? "Y" : "N") << "\n";
        getline(str, s);
        fstream f, fout("./data/temp.csv", ios::out);
        f.open("./data/patients.csv", ios::in);
        while (getline(f, temp))
            if (temp != s)
                fout << temp << "\n";
        f.close();
        fout.close();
        s.erase();
        temp.erase();
        remove("./data/patients.csv");
        rename("./data/temp.csv", "./data/patients.csv");
        str << firstName << "," << lastName
            << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
            << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
            << ","
            << ((alive) ? "Y" : "N")
            << ",N"
            << "\n";
        getline(str, s);
        f.open("./data/patientsHistory.csv", ios::in);
        fout.open("./data/temp.csv", ios::out);
        while (getline(f, temp))
        {
            if (temp == s)
            {
                fout << firstName << "," << lastName
                     << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr()
                     << "," << height << "," << weight << "," << ((hospitalized) ? "Y" : "N")
                     << ","
                     << ((alive) ? "Y" : "N")
                     << ",Y"
                     << "\n";
            }
            else
                fout << temp << "\n";
        }
        f.close();
        fout.close();
        s.erase();
        temp.erase();
        remove("./data/patientsHistory.csv");
        rename("./data/temp.csv", "./data/patientsHistory.csv");
        cout << firstName << " " << lastName << " discharged!\n";
        return;
    }
};
#endif // !PATIENT