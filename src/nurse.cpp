using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./../include/global.hh"
#include "./../include/nurse.hh"

nurse::nurse()
{
    id = -1;
    type = "";
    cat = "nurse";
    category = 3;
}
void nurse::addPerson()
{
    //18 and 65 are the age limits for registration of a new nurse;
    person::addPerson(18, 65);
    if ((age < 18) || (age > 65))
        return;
    cout << "\nEnter the type of the nurse: \n";
    getline(cin >> ws, type);
    //creating a fstream object to read/write from/to files;
    fstream f;
    //opening the file to read it;
    f.open("./data/nurses.csv", ios::in);

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
    //creating a record in nurses.csv;
    f.open("./data/nurses.csv", ios::app);
    f << id << "," << firstName << "," << lastName << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr() << "," << type << endl;
    f.close();

    //creating a record in nursesHistory.csv;
    f.open("./data/nursesHistory.csv", ios::app);
    f << firstName << "," << lastName << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr() << "," << type << ",N,NA" << endl;
    f.close();

    cout << "\n"
         << firstName << " " << lastName << " registered successfully!\n";
    cout << "Their ID is: " << id << "\n";

    return;
}
void nurse::printDetails()
{
    if (id == -1)
        return;
    person::printDetails();
    cout << "Type            : " << type << "\n";
    return;
}
void nurse::printDetailsFromHistory(string extraDetails)
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
        f.open("./data/nursesHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            nurse n;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4, s5, s7;
            //reading from the string stream object 's';
            getline(s, n.firstName, ',');
            getline(s, n.lastName, ',');
            getline(s, s4, ',');
            getline(s, s5, ',');
            getline(s, n.mobNumber, ',');

            if (n.firstName == firstName && n.lastName == lastName && n.mobNumber == mobNumber)
            {

                getline(s, s7, ',');
                getline(s, n.type, ',');
                getline(s, s1, ',');
                getline(s, s2, ',');
            }
        }
        f.close();
    }
    cout << "Type            : " << type << "\n";
    cout << "Left Work?      : " << s1 << "\n";
    if (s1 == "Y")
        cout << "Reason          : " << s2 << "\n";
    return;
}
void nurse::getDetails(int rec)
{
    int opt = 0;
    cout << "\nOPTIONS:\n[1]: Filter by ID\n[2]: Filter by Name\n[3]: Filter by Type\n\n";
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
            string s1, s4, s5, s7;
            //reading from the string stream object 's';
            getline(s, s1, ',');

            if (reqId == strToNum(s1))
            {
                f.close();
                getline(s, firstName, ',');
                getline(s, lastName, ',');
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, mobNumber, ',');
                getline(s, s7, ',');
                getline(s, type, ',');
                id = reqId;
                gender = s4[0];
                age = strToNum(s5);
                add.strToAdd(s7);
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
        getline(cin, reqLName);
        vector<nurse> matchingRecords;
        fstream f;
        f.open("./data/nurses.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            nurse n;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s1, s4, s5, s7;
            //reading from the string stream object 's';
            getline(s, s1, ',');
            getline(s, n.firstName, ',');
            getline(s, n.lastName, ',');

            if (n.firstName == reqFName && n.lastName == reqLName)
            {
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, n.mobNumber, ',');
                getline(s, s7, ',');
                getline(s, n.type, ',');
                n.id = strToNum(s1);
                n.gender = s4[0];
                n.age = strToNum(s5);
                n.add.strToAdd(s7);
                matchingRecords.push_back(n);
            }
        }
        f.close();
        cout << "\n";
        cout << matchingRecords.size() << " matching record(s) found!\n";
        for (auto i : matchingRecords)
            i.printDetails();
        char tt = 'N';
        if (matchingRecords.size() > rec)
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
                        add = i.add;
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
            nurse n;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s1, s4, s5, s7;
            //reading from the string stream object 's';
            getline(s, s1, ',');
            getline(s, n.firstName, ',');
            getline(s, n.lastName, ',');
            getline(s, s4, ',');
            getline(s, s5, ',');
            getline(s, n.mobNumber, ',');
            getline(s, s7, ',');
            getline(s, n.type, ',');
            if (n.type == reqType)
            {
                n.id = strToNum(s1);
                n.gender = s4[0];
                n.age = strToNum(s5);
                n.add.strToAdd(s7);
                matchingRecords.push_back(n);
            }
        }
        f.close();
        cout << "\n";
        cout << matchingRecords.size() << " matching record(s) found!\n";
        for (auto i : matchingRecords)
            i.printDetails();
        char tt = 'N';
        if (matchingRecords.size() > rec)
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
                        add = i.add;
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
void nurse::getDetailsFromHistory()
{
    int opt = 0;
    cout << "\nOPTIONS:\n[1]: Filter by Name\n[2]: Filter by Type\n\n";
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
            nurse n;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4, s5, s7, s9;
            //reading from the string stream object 's';
            getline(s, n.firstName, ',');
            getline(s, n.lastName, ',');

            if (n.firstName == reqFName && n.lastName == reqLName)
            {
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, n.mobNumber, ',');
                getline(s, s7, ',');
                getline(s, n.type, ',');
                getline(s, s9);
                n.id = 0;
                n.gender = s4[0];
                n.age = strToNum(s5);
                n.add.strToAdd(s7);
                matchingRecords.push_back(n);
                extraDetails.push_back(s9);
            }
        }
        f.close();
        cout << "\n";
        cout << matchingRecords.size() << " matching record(s) found!\n";
        for (int i = 0; i < matchingRecords.size(); i++)
            matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
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
            nurse n;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4, s5, s7, s9;
            //reading from the string stream object 's';
            getline(s, n.firstName, ',');
            getline(s, n.lastName, ',');
            getline(s, s4, ',');
            getline(s, s5, ',');
            getline(s, n.mobNumber, ',');
            getline(s, s7, ',');
            getline(s, n.type, ',');
            if (n.type == reqType)
            {
                getline(s, s9);
                n.id = 0;
                n.gender = s4[0];
                n.age = strToNum(s5);
                n.add.strToAdd(s7);
                matchingRecords.push_back(n);
                extraDetails.push_back(s9);
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
void nurse::removePerson()
{
    cout << "\nSearch for the nurse you want to remove.\n";
    getDetails();
    if (id == -1)
        return;
    string s, temp;
    stringstream str(s);
    str << id << "," << firstName << "," << lastName << "," << gender << "," << age
        << "," << mobNumber << "," << add.addToStr() << "," << type << "\n";
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
        << "," << mobNumber << "," << add.addToStr() << "," << type << ",N,NA\n";
    getline(str, s);
    f.open("./data/nursesHistory.csv", ios::in);
    fout.open("./data/temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
        {
            fout << firstName << "," << lastName << "," << gender << "," << age
                 << "," << mobNumber << "," << add.addToStr() << "," << type << ",Y," << reason << "\n";
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