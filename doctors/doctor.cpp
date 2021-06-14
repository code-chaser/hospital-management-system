#ifndef DOCTOR
#define DOCTOR
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
int strToNum(string s)
{
    int n = s.size(), res = 0;
    while (n--)
        res += (s[s.size() - 1 - n] - '0') * pow(10, n);
    return res;
}
class doctor
{
private:
    int id = 0;
    string firstName, lastName;
    char gender;
    int16_t age = 0;
    string type;

public:
    doctor()
    {
        id = -1;
    }
    void printDetails()
    {
        if (id == -1)
            return;
        cout << "\nDeatils:\n";
        cout << "ID:        " << id << "\n";
        cout << "Full Name: " << firstName << " " << lastName << "\n";
        cout << "Gender:    " << gender << "\n";
        cout << "Age:       " << age << "\n";
        cout << "Type:      " << type << "\n";
        return;
    }
    void addADoctor()
    {
        //creating a fstream object to read/write from files;
        fstream f;
        //opening the file to read it;
        f.open("./doctors/doctors.csv", ios::in);
        //reading the whole file just to know the total number of lines present and hence the doctor ID;
        while (getline(f >> ws, firstName))
            id++;
        f.close();
        //getting the basic details of doctor from the user side;
        cout << "\nEnter the name of the doctor: \nFirst Name:\n";
        getline(cin >> ws, firstName);
        cout << "\nLast name:\n";
        getline(cin >> ws, lastName);

        cout << "\nEnter the age of the doctor: \n";
        cin >> age;
        while (age <= 0)
            cout << "Was that supposed to make any kind of sense?\nEnter again!\n", cin >> age;

        cout << "\nEnter the gender of the doctor (M = Male || F = Female): \n";
        cin >> gender;
        while (gender != 'M' && gender != 'F')
            cout << "M or F?\n", cin >> gender;

        cout << "\nEnter the type of the doctor: \n";
        getline(cin >> ws, type);

        //opening the file to append the details of the new doctor;
        f.open("./doctors/doctors.csv", ios::app);
        f << id << "," << firstName << "," << lastName << "," << gender << "," << age << "," << type << endl;
        f.close();

        cout << "\n"
             << firstName << " " << lastName << " added successfully!\n";
        cout << "Their ID is: " << id << "\n";

        return;
    }
    void getADoctor()
    {
        int opt = 0;
        cout << "OPTIONS:\n1: Filter by ID\n2: Filter by name\n3: Filter by type\n";
        cin >> opt;
        while (opt != 1 && opt != 2 && opt != 3)
            cout << "option 1, 2 or 3?\n", cin >> opt;
        if (opt == 1)
        {
            int reqId;
            cout << "\nEnter ID:\n";
            cin >> reqId;
            fstream f;
            f.open("./doctors/doctors.csv", ios::in);
            string temp;
            while (getline(f >> ws, temp))
            {
                stringstream s(temp);
                string s1, s4, s5;
                getline(s, s1, ',');
                if (reqId == strToNum(s1))
                {
                    getline(s, firstName, ',');
                    getline(s, lastName, ',');
                    getline(s, s4, ',');
                    getline(s, s5, ',');
                    getline(s, type, ',');
                    id = reqId;
                    gender = s4[0];
                    age = strToNum(s5);
                    return;
                }
            }
            cout << "\nNo record found!\n";
        }
        else if (opt == 2)
        {
            string reqFName, reqLName;
            cout << "First Name:\n";
            getline(cin >> ws, reqFName);
            cout << "\nLast Name:\n";
            getline(cin >> ws, reqLName);
            vector<doctor> availableDoctors;
            fstream f;
            f.open("./doctors/doctors.csv", ios::in);
            string temp;
            while (getline(f >> ws, temp))
            {
                doctor d;
                stringstream s(temp);
                string s1, s4, s5;
                getline(s, s1, ',');
                getline(s, d.firstName, ',');
                getline(s, d.lastName, ',');
                if (d.firstName == reqFName && d.lastName == reqLName)
                {
                    getline(s, s4, ',');
                    getline(s, s5, ',');
                    getline(s, d.type, ',');
                    d.id = strToNum(s1);
                    d.gender = s4[0];
                    d.age = strToNum(s5);
                    availableDoctors.push_back(d);
                }
            }
            cout << "\n"
                 << availableDoctors.size() << " record(s) found!\n";
            for (auto i : availableDoctors)
                i.printDetails();
            char tt = 'N';
            if (availableDoctors.size() > 1)
            {
                do
                {
                    int reqId;
                    cout << "\nEnter the ID of the required doctor: ";
                    cin >> reqId;
                    for (auto i : availableDoctors)
                        if (reqId == i.id)
                        {
                            id = i.id;
                            firstName = i.firstName;
                            lastName = i.lastName;
                            gender = i.gender;
                            age = i.age;
                            type = i.type;
                            return;
                        }
                    cout << "Invalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> tt;
                } while (tt == 'Y');
            }
        }
        else if (opt == 3)
        {
            string reqType;
            cout << "Enter the type of doctor required:\n";
            getline(cin >> ws, reqType);
            vector<doctor> availableDoctors;
            fstream f;
            f.open("./doctors/doctors.csv", ios::in);
            string temp;
            while (getline(f >> ws, temp))
            {
                doctor d;
                stringstream s(temp);
                string s1, s4, s5;
                getline(s, s1, ',');
                getline(s, d.firstName, ',');
                getline(s, d.lastName, ',');
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, d.type, ',');
                if (d.type == reqType)
                {
                    d.id = strToNum(s1);
                    d.gender = s4[0];
                    d.age = strToNum(s5);
                    availableDoctors.push_back(d);
                }
            }
            cout << "\n"
                 << availableDoctors.size() << " record(s) found!\n";
            for (auto i : availableDoctors)
                i.printDetails();
            char tt = 'N';
            if (availableDoctors.size() > 1)
                do
                {
                    int reqId;
                    cout << "\nEnter the ID of the required doctor: ";
                    cin >> reqId;
                    for (auto i : availableDoctors)
                        if (reqId == i.id)
                        {
                            id = i.id;
                            firstName = i.firstName;
                            lastName = i.lastName;
                            gender = i.gender;
                            age = i.age;
                            type = i.type;
                            return;
                        }
                    cout << "Invalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> tt;
                } while (tt == 'Y');
        }
        return;
    }
};
#endif // !DOCTOR