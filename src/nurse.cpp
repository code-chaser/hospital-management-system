using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/nurse.hh"
#include "./../include/hospital.hh"

nurse::nurse()
{
    id = -1;
    type = "";
    cat = "nurse";
    category = 3;
}
void nurse::fillMap()
{
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
        n.id = strToNum(s1);
        n.gender = s4[0];
        n.age = strToNum(s5);
        n.add.strToAdd(s7);
        hospital::nursesList[n.id] = n;
    }
    f.close();
    return;
}
void nurse::saveMap()
{
    fstream f;
    f.open("./data/temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "nurseId,firstName,lastName,gender,age,mobNumber,address,type\n";
    for (auto i : hospital::nursesList)
        f << i.second.id << "," << i.second.firstName << "," << i.second.lastName << "," << i.second.gender
          << "," << i.second.age << "," << i.second.mobNumber << "," << i.second.add.addToStr()
          << "," << i.second.type << endl;
    f.close();
    remove("./data/nurses.csv");
    rename("./data/temp.csv", "./data/nurses.csv");
    return;
}
void nurse::addPerson()
{
    if (hospital::nursesList.size() == hospital::nursesLimit)
    {
        cout << "\n\nNurses limit reached, can't add more!\n\n";
        return;
    }
    //18 and 65 are the age limits for registration of a new nurse;
    person::addPerson(18, 65);
    if ((age < 18) || (age > 65))
        return;
    cout << "\nEnter the type of the nurse: \n";
    getline(cin >> ws, type);
    if (hospital::nursesList.rbegin() != hospital::nursesList.rend())
        id = ((hospital::nursesList.rbegin())->first) + 1;
    else
        id = 1;
    hospital::nursesList[id] = *this;

    //creating a fstream object to read/write from/to files;
    fstream f;
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
        if (hospital::nursesList.find(reqId) != hospital::nursesList.end())
            *this = hospital::nursesList[reqId];
        else
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
        vector<nurse> matchingRecords;
        for (auto i : hospital::nursesList)
        {
            if (i.second.firstName == reqFName && i.second.lastName == reqLName)
                matchingRecords.push_back(i.second);
        }
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
                if (hospital::nursesList.find(reqId) != hospital::nursesList.end())
                    *this = hospital::nursesList[reqId];
                else
                {
                    cout << "\nInvalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> tt;
                    while (tt != 'Y' || tt != 'N')
                        cout << "Y or N?\n", cin >> tt;
                }
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
        for (auto i : hospital::nursesList)
        {
            if (i.second.type == reqType)
                matchingRecords.push_back(i.second);
        }
        cout << "\n";
        cout << matchingRecords.size() << " matching record(s) found!\n";
        for (auto i : matchingRecords)
            i.printDetails();
        char tt = 'N';
        if (matchingRecords.size() > 0)
            do
            {
                int reqId;
                cout << "\nEnter the ID of the required nurse: ";
                cin >> reqId;
                if (hospital::nursesList.find(reqId) != hospital::nursesList.end())
                    *this = hospital::nursesList[reqId];
                else
                {
                    cout << "\nInvalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> tt;
                    while (tt != 'Y' || tt != 'N')
                        cout << "Y or N?\n", cin >> tt;
                }
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
    hospital::nursesList.erase(id);

    string s, temp;
    stringstream str;
    fstream f, fout;
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