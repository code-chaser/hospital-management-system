using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./../headerFiles/global.hh"
#include "./../headerFiles/appointment.hh"

appointment::appointment()
{
    id = -1;
    D.id = -1;
    P.id = -1;
}
appointment::~appointment()
{
    id = -1;
    D.id = -1;
    P.id = -1;
    return;
}
void appointment::printDetails()
{
    if (id == -1)
        return;
    cout << "\n\n\nAppointment Details:\nID                 : " << id << "\n"
         << "Patient's Name     : " + P.firstName + " " + P.lastName + "(ID = " << P.id << ")\n"
         << "Doctor's Name      : " + D.firstName + " " + D.lastName + "(ID = " << D.id << ")\n"
         << "Time (24 Hr format): " << hh << ":00 Hrs to " << hh + 1 << ":00 Hrs\n\n";
    return;
}
void appointment::book()
{
    cout << "\n\nIs the patient already registered (Y : Yes || N : No)?\n";
    char ans;
    cin >> ans;
    while (ans != 'Y' && ans != 'N')
    {
        cout << "Y or N?\n";
        cin >> ans;
    }
    if (ans == 'N')
    {
        cout << "Register the patient:\n";
        P.addPerson();
    }
    else
    {
        cout << "Search for the required patient:\n\n";
        ans = 'Y';
        while (ans == 'Y')
        {
            P.getDetails();
            ans = 'K';
            if (P.id == -1)
            {
                cout << "Invalid selection!\n";
                cout << "Try again (Y : Yes || N : No)?\n";
                cin >> ans;
                while (ans != 'Y' && ans != 'N')
                {
                    cout << "Y or N?\n";
                    cin >> ans;
                }
            }
        }
        if (ans == 'N')
        {
            return;
        }
    }
    cout << "\n\nNow, search for the required doctor:\n";
    ans = 'Y';
    while (ans == 'Y')
    {
        D.getDetails();
        ans = 'K';
        if (D.id == -1)
        {
            cout << "Invalid selection!\n";
            cout << "Try again (Y : Yes || N : No)?\n";
            cin >> ans;
            while (ans != 'Y' && ans != 'N')
            {
                cout << "Y or N?\n";
                cin >> ans;
            }
        }
        else if (D.appointmentsBooked >= 8)
        {
            cout << "Sorry, selected doctor has no free slot left for the day!\n";
            cout << "Search again (Y : Yes || N : No)?\n";
            cin >> ans;
            while (ans != 'Y' && ans != 'N')
            {
                cout << "Y or N?\n";
                cin >> ans;
            }
        }
    }
    if (ans == 'N')
    {
        return;
    }
    //creating a fstream object to read/write from/to files;
    fstream f;
    //opening the file to read it;
    f.open("./data/appointments.csv", ios::in);

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
    //creating a record in appointments.csv;
    f.open("./data/appointments.csv", ios::app);
    f << id << "," << date << "," << D.id << "," << P.id << "," << D.appointmentsBooked + 9 << endl;
    f.close();

    string initial, corrected;
    stringstream str;
    str << D.id << "," << D.firstName << "," << D.lastName << ","
        << D.gender << "," << D.age << "," << D.mobNumber << ","
        << D.add.addToStr() << "," << D.type << "," << D.appointmentsBooked;
    getline(str, initial);
    corrected = initial;
    corrected[corrected.size() - 1]++;
    fstream fout("./data/temp.csv", ios::out);
    f.open("./data/doctors.csv", ios::in);
    while (getline(f, temp))
    {
        if (temp == initial)
        {
            fout << corrected << "\n";
        }
        else
        {
            fout << temp << "\n";
        }
    }
    f.close();
    fout.close();
    remove("./data/doctors.csv");
    rename("./data/temp.csv", "./data/doctors.csv");
    cout << "\nAppointment of patient " + P.firstName + " " + P.lastName + " with doctor "
         << D.firstName << " " << D.lastName << " booked successfully!\n";
    printDetails();
    D.appointmentsBooked++;
    return;
}
void appointment::fillDetails()
{
    fstream f("./data/appointments.csv");
    string temp;
    getline(f, temp);
    while (getline(f, temp))
    {
        stringstream str(temp);
        string s1, s2, s3, s4, s5;
        getline(str, s1, ',');
        if (strToNum(s1) == id)
        {
            getline(str, s2, ',');
            getline(str, s3, ',');
            getline(str, s4, ',');
            getline(str, s5, ',');
            // s2 is date, of no use!
            D.id = strToNum(s3);
            P.id = strToNum(s4);
            hh = strToNum(s5);
            break;
        }
    }
    f.close();
    f.open("./data/doctors.csv", ios::in);
    temp;
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

        if (D.id == strToNum(s1))
        {
            getline(s, D.firstName, ',');
            getline(s, D.lastName, ',');
            getline(s, s4, ',');
            getline(s, s5, ',');
            getline(s, D.mobNumber, ',');
            getline(s, s7, ',');
            getline(s, D.type, ',');
            getline(s, s9, ',');
            D.gender = s4[0];
            D.age = strToNum(s5);
            D.add.strToAdd(s7);
            D.appointmentsBooked = strToNum(s9);
            break;
        }
    }
    f.close();
    f.open("./data/patients.csv", ios::in);
    temp;
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

        if (P.id == strToNum(s1))
        {
            getline(s, P.firstName, ',');
            getline(s, P.lastName, ',');
            getline(s, s4, ',');
            getline(s, s5, ',');
            getline(s, P.mobNumber, ',');
            getline(s, s7, ',');
            getline(s, s8, ',');
            getline(s, s9, ',');
            getline(s, s10, ',');
            getline(s, s11, ',');
            P.gender = s4[0];
            P.age = strToNum(s5);
            P.add.strToAdd(s7);
            P.height = strToNum(s8);
            P.weight = strToNum(s9);
            P.hospitalized = (s10 == "Y");
            P.alive = (s11 == "Y");
            break;
        }
    }
    f.close();
    return;
}
void appointment::getDetails()
{
    cout << "\nEnter appointment ID:\n";
    cin >> id;
    fillDetails();
    return;
}
void appointment::printAll()
{
    fstream f("./data/appointments.csv");
    string temp;
    getline(f, temp);
    while (getline(f, temp))
    {
        stringstream str(temp);
        string s1;
        getline(str, s1, ',');
        id = strToNum(s1);
        fillDetails();
        printDetails();
    }
    f.close();
    return;
}