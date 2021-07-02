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
    bool idle = 1;

public:
    driver()
    {
        id = -1;
        cat = "driver";
        category = 4;
    }
    void addPerson()
    {
        //18 and 65 are the age limits for registration of a new driver;
        person::addPerson(18, 65);
        if ((age < 18) || (age > 65))
            return;
        cout << "\nEnter the license number of the driver: \n";
        getline(cin >> ws, licenseNumber);
        //creating a fstream object to read/write from/to files;
        fstream f;
        //opening the file to read it;
        f.open("./data/drivers.csv", ios::in);
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
        temp.erase();
        idString.erase();
        //creating a record in drivers.csv;
        f.open("./data/drivers.csv", ios::app);
        f << id << "," << firstName << "," << lastName << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr() << "," << licenseNumber << ",Y" << endl;
        f.close();

        //creating a record in driversHistory.csv;
        f.open("./data/driversHistory.csv", ios::app);
        f << firstName << "," << lastName << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr() << "," << licenseNumber << ",N,NA" << endl;
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
        cout << "License Number  : " << licenseNumber << "\n";
        cout << "Idle?           : " << (idle ? "Y\n" : "N\n");
        return;
    }
    void printDetailsFromHistory(string extraDetails = "")
    {
        if (id == -1)
            return;
        person::printDetailsFromHistory();
        stringstream k(extraDetails);
        string s1, s2;
        getline(k, s1, ',');
        getline(k, s2, ',');
        if (extraDetails == "")
        {
            fstream f;
            f.open("./data/driversHistory.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                driver d;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s4, s5, s7;
                //reading from the string stream object 's';
                getline(s, d.firstName, ',');
                getline(s, d.lastName, ',');
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, d.mobNumber, ',');

                if (d.firstName == firstName && d.lastName == lastName && d.mobNumber == mobNumber)
                {
                    getline(s, s7, ',');
                    getline(s, d.licenseNumber, ',');
                    getline(s, s1, ',');
                    getline(s, s2, ',');
                }
            }
            f.close();
        }
        cout << "License Number  : " << licenseNumber << "\n";
        cout << "Left Work?      : " << s1 << "\n";
        if (s1 == "Y")
            cout << "Reason          : " << s2 << "\n";
        return;
    }
    void getDetails()
    {
        int opt = 0;
        cout << "\nOPTIONS:\n[1]: Filter by ID\n[2]: Filter by Name\n[3]: Filter by License Number\n\n";
        cin >> opt;
        while (opt != 1 && opt != 2 && opt != 3)
            cout << "option 1, 2 or 3?\n", cin >> opt;
        //1: Filter by ID;
        if (opt == 1)
        {
            int reqId;
            cout << "\nEnter ID:\n";
            cin >> reqId;

            fstream f;
            f.open("./data/drivers.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s1, s4, s5, s7, s9;
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
                    getline(s, licenseNumber, ',');
                    getline(s, s9, ',');
                    id = reqId;
                    gender = s4[0];
                    age = strToNum(s5);
                    add.strToAdd(s7);
                    idle = (s9 == "Y");
                    return;
                }
            }
            f.close();
            //if a record is found, it's details will be stored in the driver class object that called this function,
            //and the control is returned;
            //else:
            cout << "\nNo matching record found!\n";
        }
        //2: Filter by name;
        else if (opt == 2)
        {
            string reqFName, reqLName;
            cout << "First Name:\n";
            getline(cin >> ws, reqFName);
            cout << "\nLast Name:\n";
            getline(cin, reqLName);
            vector<driver> matchingRecords;
            fstream f;
            f.open("./data/drivers.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                driver d;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s1, s4, s5, s7, s9;
                //reading from the string stream object 's';
                getline(s, s1, ',');
                getline(s, d.firstName, ',');
                getline(s, d.lastName, ',');

                if (d.firstName == reqFName && d.lastName == reqLName)
                {
                    getline(s, s4, ',');
                    getline(s, s5, ',');
                    getline(s, d.mobNumber, ',');
                    getline(s, s7, ',');
                    getline(s, d.licenseNumber, ',');
                    getline(s, s9, ',');
                    d.id = strToNum(s1);
                    d.gender = s4[0];
                    d.age = strToNum(s5);
                    d.add.strToAdd(s7);
                    d.idle = (s9 == "Y");
                    matchingRecords.push_back(d);
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
                    cout << "\nEnter the ID of the required driver: ";
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
                            licenseNumber = i.licenseNumber;
                            idle = i.idle;
                            return;
                        }
                    cout << "\nInvalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> tt;
                    while (tt != 'Y' || tt != 'N')
                        cout << "Y or N?\n", cin >> tt;
                } while (tt == 'Y');
            }
        }
        //3: Filter by licenseNumber;
        else if (opt == 3)
        {
            string reqlicenseNumber;
            cout << "Enter the license number of driver required:\n";
            getline(cin >> ws, reqlicenseNumber);
            fstream f;
            f.open("./data/drivers.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s1, s4, s5, s7, s9;
                //reading from the string stream object 's';
                getline(s, s1, ',');
                getline(s, firstName, ',');
                getline(s, lastName, ',');
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, mobNumber, ',');
                getline(s, s7, ',');
                getline(s, licenseNumber, ',');
                if (licenseNumber == reqlicenseNumber)
                {

                    getline(s, s9, ',');
                    id = strToNum(s1);
                    gender = s4[0];
                    age = strToNum(s5);
                    add.strToAdd(s7);
                    idle = (s9 == "Y");
                    return;
                }
            }
            f.close();
            //if a record is found, it's details will be stored in the driver class object that called this function,
            //and the control is returned;
            //else:
            cout << "\nNo matching record found!\n";
        }
        return;
    }
    void getDetailsFromHistory()
    {
        int opt = 0;
        cout << "\nOPTIONS:\n[1]: Filter by Name\n[2]: Filter by License Number\n\n";
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
            vector<driver> matchingRecords;
            vector<string> extraDetails;
            fstream f;
            f.open("./data/driversHistory.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                driver d;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s4, s5, s7, s9;
                //reading from the string stream object 's';
                getline(s, d.firstName, ',');
                getline(s, d.lastName, ',');

                if (d.firstName == reqFName && d.lastName == reqLName)
                {
                    getline(s, s4, ',');
                    getline(s, s5, ',');
                    getline(s, d.mobNumber, ',');
                    getline(s, s7, ',');
                    getline(s, d.licenseNumber, ',');
                    getline(s, s9);
                    d.id = 0;
                    d.gender = s4[0];
                    d.age = strToNum(s5);
                    d.add.strToAdd(s7);
                    matchingRecords.push_back(d);
                    extraDetails.push_back(s9);
                }
            }
            f.close();
            cout << "\n";
            cout << matchingRecords.size() << " matching record(s) found!\n";
            for (int i = 0; i < matchingRecords.size(); i++)
                matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
        }
        //2: Filter by licenseNumber;
        else if (opt == 2)
        {
            string reqlicenseNumber;
            cout << "Enter the licenseNumber of driver required:\n";
            getline(cin >> ws, reqlicenseNumber);
            vector<driver> matchingRecords;
            vector<string> extraDetails;
            fstream f;
            f.open("./data/driversHistory.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s4, s5, s7, s9;
                //reading from the string stream object 's';
                getline(s, firstName, ',');
                getline(s, lastName, ',');
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, mobNumber, ',');
                getline(s, s7, ',');
                getline(s, licenseNumber, ',');
                if (licenseNumber == reqlicenseNumber)
                {
                    getline(s, s9);
                    id = 0;
                    gender = s4[0];
                    age = strToNum(s5);
                    add.strToAdd(s7);
                    printDetailsFromHistory(s9);
                    return;
                }
            }
            f.close();
            //if a record is found, it's details will be stored in the driver class object that called this function,
            //and the control is returned;
            //else:
            cout << "\nNo matching record found!\n";
        }
        return;
    }
    void removePerson()
    {
        cout << "\nSearch for the driver you want to remove.\n";
        getDetails();
        if (!idle)
        {
            cout << "\nSorry, the driver you selected to remove is not currently idle.\nOnly idlers can be removed.\n\n";
            return;
        }
        string s, temp;
        stringstream str(s);
        str << id << "," << firstName << "," << lastName << "," << gender << "," << age
            << "," << mobNumber << "," << add.addToStr() << "," << licenseNumber << ",Y\n";
        getline(str, s);
        fstream f, fout("./data/temp.csv", ios::out);
        f.open("./data/drivers.csv", ios::in);
        while (getline(f, temp))
            if (temp != s)
                fout << temp << "\n";
        f.close();
        fout.close();
        s.erase();
        temp.erase();
        remove("./data/drivers.csv");
        rename("./data/temp.csv", "./data/drivers.csv");
        string reason;
        cout << "\nReason?\n";
        getline(cin >> ws, reason);
        str << firstName << "," << lastName << "," << gender << "," << age
            << "," << mobNumber << "," << add.addToStr() << "," << licenseNumber << ",N,NA\n";
        getline(str, s);
        f.open("./data/driversHistory.csv", ios::in);
        fout.open("./data/temp.csv", ios::out);
        while (getline(f, temp))
        {
            if (temp == s)
            {
                fout << firstName << "," << lastName << "," << gender << "," << age
                     << "," << mobNumber << "," << add.addToStr() << "," << licenseNumber << ",Y," << reason << "\n";
            }
            else
                fout << temp << "\n";
        }
        f.close();
        fout.close();
        s.erase();
        temp.erase();
        remove("./data/driversHistory.csv");
        rename("./data/temp.csv", "./data/driversHistory.csv");
        cout << firstName << " " << lastName << " removed successfully!\n";
        return;
    }
};
#endif // !DRIVER