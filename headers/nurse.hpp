#ifndef NURSE
#define NURSE
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./person.hpp"
class nurse : public person
{
protected:
    string type = "";

public:
    nurse()
    {
        id = -1;
        cat = "nurse";
        category = 3;
    }
    void printDetails()
    {
        if (id == -1)
            return;
        printPersonDetails();
        cout << "Type            : " << type << "\n";
        return;
    }
    void printHistoryDetails(string extraDetails = "")
    {
        if (id == -1)
            return;
        printPersonHistoryDetails();
        stringstream k(extraDetails);
        string s1, s2;
        getline(k, s1, ',');
        getline(k, s2, ',');
        if (extraDetails == "")
        {
            fstream f;
            f.open("./data/nursesHistory.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                nurse d;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s4, s5;
                //reading from the string stream object 's';
                getline(s, d.firstName, ',');
                getline(s, d.lastName, ',');
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, d.mobNumber, ',');

                if (d.firstName == firstName && d.lastName == lastName && d.mobNumber == mobNumber)
                {

                    getline(s, d.address, ',');
                    getline(s, d.type, ',');
                    getline(s, s1, ',');
                    getline(s, s2, ',');
                }
            }
            f.close();
        }
        cout << "Type            : " << type << "\n";
        cout << "Left Work?      : " << s1 << "\n";
        cout << "Reason (if left): " << s2 << "\n";
        return;
    }
    void addANurse()
    {
        //18 and 65 are the age limits for registration of a new nurse;
        setDetails(18, 65);
        if ((age < 18) || (age > 65))
            return;
        cout << "\nEnter the type of the nurse: \n";
        getline(cin >> ws, type);
        //creating a fstream object to read/write from/to files;
        fstream f;
        //opening the file to read it;
        f.open("./data/nurses.csv", ios::in);
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
        temp.erase();
        idString.erase();
        //creating a record in nurses.csv;
        f.open("./data/nurses.csv", ios::app);
        f << id << "," << firstName << "," << lastName << "," << gender << "," << age << "," << mobNumber << "," << address << "," << type << endl;
        f.close();

        //creating a record in nursesHistory.csv;
        f.open("./data/nursesHistory.csv", ios::app);
        f << firstName << "," << lastName << "," << gender << "," << age << "," << mobNumber << "," << address << "," << type << ",N,NA" << endl;
        f.close();

        cout << "\n"
             << firstName << " " << lastName << " added successfully!\n";
        cout << "Their ID is: " << id << "\n";

        return;
    }
    void getDetails()
    {
        int opt = 0;
        cout << "\nOPTIONS:\n[1]: Filter by ID\n[2]: Filter by name\n[3]: Filter by type\n\n";
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
            f.open("./data/nurses.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s1, s4, s5;
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
                    getline(s, type, ',');
                    id = reqId;
                    gender = s4[0];
                    age = strToNum(s5);
                    return;
                }
            }
            f.close();
            //if a record is found, it's details will be stored in the nurse class object that called this function,
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
            vector<nurse> matchingRecords;
            fstream f;
            f.open("./data/nurses.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                nurse d;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s1, s4, s5;
                //reading from the string stream object 's';
                getline(s, s1, ',');
                getline(s, d.firstName, ',');
                getline(s, d.lastName, ',');

                if (d.firstName == reqFName && d.lastName == reqLName)
                {
                    getline(s, s4, ',');
                    getline(s, s5, ',');
                    getline(s, d.mobNumber, ',');
                    getline(s, d.address, ',');
                    getline(s, d.type, ',');
                    d.id = strToNum(s1);
                    d.gender = s4[0];
                    d.age = strToNum(s5);
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
                    cout << "\nEnter the ID of the required nurse: ";
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
                            type = i.type;
                            return;
                        }
                    cout << "\nInvalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> tt;
                    while (tt != 'Y' || tt != 'N')
                        cout << "Y or N?\n", cin >> tt;
                } while (tt == 'Y');
            }
        }
        //3: Filter by type;
        else if (opt == 3)
        {
            string reqType;
            cout << "Enter the type of nurse required:\n";
            getline(cin >> ws, reqType);
            vector<nurse> matchingRecords;
            fstream f;
            f.open("./data/nurses.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                nurse d;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s1, s4, s5;
                //reading from the string stream object 's';
                getline(s, s1, ',');
                getline(s, d.firstName, ',');
                getline(s, d.lastName, ',');
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, d.mobNumber, ',');
                getline(s, d.address, ',');
                getline(s, d.type, ',');
                if (d.type == reqType)
                {
                    d.id = strToNum(s1);
                    d.gender = s4[0];
                    d.age = strToNum(s5);
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
                do
                {
                    int reqId;
                    cout << "\nEnter the ID of the required nurse: ";
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
                            type = i.type;
                            return;
                        }
                    cout << "Invalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> tt;
                    while (tt != 'Y' || tt != 'N')
                        cout << "Y or N?\n", cin >> tt;
                } while (tt == 'Y');
        }
        return;
    }
    void getDetailsFromHistory()
    {
        int opt = 0;
        cout << "\nOPTIONS:\n[1]: Filter by name\n[2]: Filter by type\n\n";
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
            getline(cin >> ws, reqLName);
            vector<nurse> matchingRecords;
            vector<string> extraDetails;
            fstream f;
            f.open("./data/nursesHistory.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                nurse d;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s4, s5, s9;
                //reading from the string stream object 's';
                getline(s, d.firstName, ',');
                getline(s, d.lastName, ',');

                if (d.firstName == reqFName && d.lastName == reqLName)
                {
                    getline(s, s4, ',');
                    getline(s, s5, ',');
                    getline(s, d.mobNumber, ',');
                    getline(s, d.address, ',');
                    getline(s, d.type, ',');
                    getline(s, s9);
                    d.id = 0;
                    d.gender = s4[0];
                    d.age = strToNum(s5);
                    matchingRecords.push_back(d);
                    extraDetails.push_back(s9);
                }
            }
            f.close();
            cout << "\n";
            cout << matchingRecords.size() << " matching record(s) found!\n";
            for (int i = 0; i < matchingRecords.size(); i++)
                matchingRecords[i].printHistoryDetails(extraDetails[i]);
        }
        //2: Filter by type;
        else if (opt == 2)
        {
            string reqType;
            cout << "Enter the type of nurse required:\n";
            getline(cin >> ws, reqType);
            vector<nurse> matchingRecords;
            vector<string> extraDetails;
            fstream f;
            f.open("./data/nursesHistory.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                nurse d;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s4, s5, s9;
                //reading from the string stream object 's';
                getline(s, d.firstName, ',');
                getline(s, d.lastName, ',');
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, d.mobNumber, ',');
                getline(s, d.address, ',');
                getline(s, d.type, ',');
                if (d.type == reqType)
                {
                    getline(s, s9);
                    d.id = 0;
                    d.gender = s4[0];
                    d.age = strToNum(s5);
                    matchingRecords.push_back(d);
                    extraDetails.push_back(s9);
                }
            }
            f.close();
            cout << "\n";
            cout << matchingRecords.size() << " matching record(s) found!\n";
            for (int i = 0; i < matchingRecords.size(); i++)
                matchingRecords[i].printHistoryDetails(extraDetails[i]);
        }
        return;
    }
    void removeANurse()
    {
        cout << "\nSearch for the nurse you want to remove.\n";
        getDetails();
        string s, temp;
        stringstream str(s);
        str << id << "," << firstName << "," << lastName << "," << gender << "," << age
            << "," << mobNumber << "," << address << "," << type << "\n";
        getline(str, s);
        fstream f, fout("./data/temp.csv", ios::out);
        f.open("./data/nurses.csv", ios::in);
        while (getline(f, temp))
            if (temp != s)
                fout << temp << "\n";
        f.close();
        fout.close();
        s.erase();
        temp.erase();
        remove("./data/nurses.csv");
        rename("./data/temp.csv", "./data/nurses.csv");
        string reason;
        cout << "\nReason?\n";
        getline(cin >> ws, reason);
        str << firstName << "," << lastName << "," << gender << "," << age
            << "," << mobNumber << "," << address << "," << type << ",N,NA\n";
        getline(str, s);
        f.open("./data/nursesHistory.csv", ios::in);
        fout.open("./data/temp.csv", ios::out);
        while (getline(f, temp))
        {
            if (temp == s)
            {
                fout << firstName << "," << lastName << "," << gender << "," << age
                     << "," << mobNumber << "," << address << "," << type << ",Y," << reason << "\n";
            }
            else
                fout << temp << "\n";
        }
        f.close();
        fout.close();
        s.erase();
        temp.erase();
        remove("./data/nursesHistory.csv");
        rename("./data/temp.csv", "./data/nursesHistory.csv");
        cout << firstName << " " << lastName << " removed successfully!\n";
        return;
    }
};
#endif // !NURSE