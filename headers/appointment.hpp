#ifndef APPOINTMENT
#define APPOINTMENT
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./patient.hpp"
#include "./doctor.hpp"
class appointment
{
private:
    int id;
    doctor D;
    patient P;
    int hh; //hh -> hour in 24 hour format;
public:
    appointment()
    {
        id = -1;
        D.id = -1;
        P.id = -1;
        fstream f;
        f.open("./data/appointments.csv", ios::in);
        string temp, s, header;
        getline(f, header);
        getline(f, temp);
        f.close();
        stringstream str(temp);
        getline(str, s, ',');
        getline(str, s, ',');
        int dd, mm, yyyy;
        if (s != "")
            cout << "\n\n\nLast usage date (DD-MM-YYY) : " << s.substr(6, 2) + "-" + s.substr(4, 2) + "-" + s.substr(0, 4) + "\n";
        cout << "\nPlease Enter Today's Date (DD-MM-YYYY) :\n\nEnter Day: ";
        cin >> dd;
        cout << "Enter Month: ";
        cin >> mm;
        cout << "Enter Year (YYYY): ";
        cin >> yyyy;
        date = yyyy * 10000 + mm * 100 + dd;
        if (strToNum(((s == "") ? ("0") : (s))) < date)
        {
            f.open("./data/temp.csv", ios::out);
            f << header << "\n";
            f.close();
            remove("./data/appointments.csv");
            rename("./data/temp.csv", "./data/appointments.csv");
            fstream fout("./data/temp.csv", ios::out);
            f.open("./data/doctors.csv", ios::in);
            getline(f, temp);
            fout << temp << endl;
            while (getline(f, temp))
            {
                if (temp.size())
                    temp[temp.size() - 1] = '0';
                fout << temp << endl;
            }
            f.close();
            fout.close();
            remove("./data/doctors.csv");
            rename("./data/temp.csv", "./data/doctors.csv");
        }
        else if (strToNum(s) > date && s != "")
        {
            cout << "/nEntered date detected wrong!\nToday's date can't be older than the last usage date, which is : "
                 << s.substr(6, 2) + "-" + s.substr(4, 2) + "-" + s.substr(0, 4) + "\n";
            return;
        }
        return;
    }
    ~appointment()
    {
        id = -1;
        D.id = -1;
        P.id = -1;
    }
    void printDetails()
    {
        if (id == -1)
            return;
        cout << "/nAppointment Details:\nID                 : " << id << "\n"
             << "Patient's Name     : " + P.firstName + " " + P.lastName + "(ID = " << P.id << ")\n"
             << "Doctor's Name      : " + D.firstName + " " + D.lastName + "(ID = " << D.id << ")\n"
             << "Time (24 Hr format): " << D.appointmentsBooked + 9 << ":00 Hrs\n\n";
        return;
    }
    void book()
    {
        cout << "/n/nIs the patient already registered (Y : Yes || N : No)?\n";
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
};
#endif // !APPOINTMENT