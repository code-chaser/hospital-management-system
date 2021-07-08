using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/doctor.hh"
#include "./../include/hospital.hh"

doctor::doctor()
{
    id = -1;
    type = "";
    appointmentsBooked = 0;
    cat = "doctor";
    category = 1;
}
void doctor::getData()
{
    fstream f;
    f.open("./data/doctors.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        doctor d;
        //creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string s1, s4, s5, s7, s9;
        //reading from the string stream object 's';
        getline(s, s1, ',');
        getline(s, d.firstName, ',');
        getline(s, d.lastName, ',');
        getline(s, s4, ',');
        getline(s, s5, ',');
        getline(s, d.mobNumber, ',');
        getline(s, s7, ',');
        getline(s, d.type, ',');
        getline(s, s9, ',');
        d.id = strToNum(s1);
        d.gender = s4[0];
        d.age = strToNum(s5);
        d.add.strToAdd(s7);
        d.appointmentsBooked = strToNum(s9);
        hospital::doctorsList[d.id] = d;
    }
    f.close();
    return;
}
void doctor::addPerson()
{
    //18 and 65 are the age limits for registration of a new doctor;
    person::addPerson(18, 65);
    if ((age < 18) || (age > 65))
        return;
    cout << "\nEnter the type of the doctor: \n";
    getline(cin >> ws, type);
    //creating a fstream object to read/write from/to files;
    fstream f;
    //opening the file to read it;
    f.open("./data/doctors.csv", ios::in);

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
    //creating a record in doctors.csv;
    f.open("./data/doctors.csv", ios::app);
    f << id << "," << firstName << "," << lastName << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr() << "," << type << ",0" << endl;
    f.close();

    //creating a record in doctorsHistory.csv;
    f.open("./data/doctorsHistory.csv", ios::app);
    f << firstName << "," << lastName << "," << gender << "," << age << "," << mobNumber << "," << add.addToStr() << "," << type << ",N,NA" << endl;
    f.close();

    cout << "\n"
         << firstName << " " << lastName << " registered successfully!\n";
    cout << "Their ID is: " << id << "\n";

    return;
}
void doctor::printDetails()
{
    if (id == -1)
        return;
    person::printDetails();
    cout << "Type            : " << type << "\n";
    cout << "Appointments    : " << appointmentsBooked << "/8 (appointments booked today)\n";
    return;
}
void doctor::printDetailsFromHistory(string extraDetails)
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
        f.open("./data/doctorsHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            doctor d;
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
                getline(s, d.type, ',');
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
void doctor::getDetails(int rec)
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
        f.open("./data/doctors.csv", ios::in);
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
                f.close();
                getline(s, firstName, ',');
                getline(s, lastName, ',');
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, mobNumber, ',');
                getline(s, s7, ',');
                getline(s, type, ',');
                getline(s, s9, ',');
                id = reqId;
                gender = s4[0];
                age = strToNum(s5);
                add.strToAdd(s7);
                appointmentsBooked = strToNum(s9);
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
        getline(cin, reqLName);
        vector<doctor> matchingRecords;
        fstream f;
        f.open("./data/doctors.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            doctor d;
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
                getline(s, d.type, ',');
                getline(s, s9, ',');
                d.id = strToNum(s1);
                d.gender = s4[0];
                d.age = strToNum(s5);
                d.add.strToAdd(s7);
                d.appointmentsBooked = strToNum(s9);
                matchingRecords.push_back(d);
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
                cout << "\nEnter the ID of the required doctor: ";
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
                        appointmentsBooked = i.appointmentsBooked;
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
        cout << "Enter the type of doctor required:\n";
        getline(cin >> ws, reqType);
        vector<doctor> matchingRecords;
        fstream f;
        f.open("./data/doctors.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            doctor d;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s1, s4, s5, s7, s9;
            //reading from the string stream object 's';
            getline(s, s1, ',');
            getline(s, d.firstName, ',');
            getline(s, d.lastName, ',');
            getline(s, s4, ',');
            getline(s, s5, ',');
            getline(s, d.mobNumber, ',');
            getline(s, s7, ',');
            getline(s, d.type, ',');
            if (d.type == reqType)
            {
                getline(s, s9, ',');
                d.id = strToNum(s1);
                d.gender = s4[0];
                d.age = strToNum(s5);
                d.add.strToAdd(s7);
                d.appointmentsBooked = strToNum(s9);
                matchingRecords.push_back(d);
            }
        }
        f.close();
        cout << "\n";
        cout << matchingRecords.size() << " matching record(s) found!\n";
        for (auto i : matchingRecords)
            i.printDetails();
        char tt = 'N';
        if (matchingRecords.size() > 0)
            do
            {
                int reqId;
                cout << "\nEnter the ID of the required doctor: ";
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
                        appointmentsBooked = i.appointmentsBooked;
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
void doctor::getDetailsFromHistory()
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
        vector<doctor> matchingRecords;
        vector<string> extraDetails;
        fstream f;
        f.open("./data/doctorsHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            doctor d;
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
                getline(s, d.type, ',');
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
    //2: Filter by type;
    else if (opt == 2)
    {
        string reqType;
        cout << "Enter the type of doctor required:\n";
        getline(cin >> ws, reqType);
        vector<doctor> matchingRecords;
        vector<string> extraDetails;
        fstream f;
        f.open("./data/doctorsHistory.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            doctor d;
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s4, s5, s7, s9;
            //reading from the string stream object 's';
            getline(s, d.firstName, ',');
            getline(s, d.lastName, ',');
            getline(s, s4, ',');
            getline(s, s5, ',');
            getline(s, d.mobNumber, ',');
            getline(s, s7, ',');
            getline(s, d.type, ',');
            if (d.type == reqType)
            {
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
    return;
}
void doctor::removePerson()
{
    cout << "\nSearch for the doctor you want to remove.\n";
    getDetails();
    if (id == -1)
        return;
    string s, temp;
    stringstream str(s);
    str << id << "," << firstName << "," << lastName << "," << gender << "," << age
        << "," << mobNumber << "," << add.addToStr() << "," << type << "," << appointmentsBooked << "\n";
    getline(str, s);
    fstream f, fout("./data/temp.csv", ios::out);
    f.open("./data/doctors.csv", ios::in);
    cout << s << "\n";
    while (getline(f, temp))
    {
        cout << "\n\n\nye s h: " << s << "\nye temp h: " << temp << "\n\n\n";
        if (temp != s)
        {
            fout << temp << "\n";
        }
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("./data/doctors.csv");
    rename("./data/temp.csv", "./data/doctors.csv");
    string reason;
    cout << "\nReason?\n";
    getline(cin >> ws, reason);
    str << firstName << "," << lastName << "," << gender << "," << age
        << "," << mobNumber << "," << add.addToStr() << "," << type << ",N,NA\n";
    getline(str, s);
    f.open("./data/doctorsHistory.csv", ios::in);
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
    remove("./data/doctorsHistory.csv");
    rename("./data/temp.csv", "./data/doctorsHistory.csv");
    cout << firstName << " " << lastName << " removed successfully!\n";
    return;
}
