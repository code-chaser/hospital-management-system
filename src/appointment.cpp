using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/appointment.hh"
#include "./../include/hospital.hh"

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
void appointment::fillMap()
{
    fstream f;
    f.open("./data/appointments.csv", ios::in);
    string temp;
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        appointment a;
        //creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string s1, s2, s3, s4, s5;
        //reading from the string stream object 's';
        getline(s, s1, ',');
        getline(s, s2, ','); // date is of no use here;
        getline(s, s3, ',');
        getline(s, s4, ',');
        getline(s, s5, ',');
        a.id = strToNum(s1);
        a.D = hospital::doctorsList[strToNum(s3)];
        a.P = hospital::patientsList[strToNum(s4)];
        a.hh = strToNum(s5);
        hospital::appointmentsList[a.id] = a;
    }
    f.close();
    return;
}
void appointment::saveMap()
{
    fstream f;
    f.open("./data/temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "appointmentId,date(YYYYMMDD),doctorId,patientId,startTime(in 24-hr format)\n";
    for (auto i : hospital::appointmentsList)
        f << i.second.id << "," << yyyymmdd << "," << i.second.D.id << "," << i.second.P.id
          << "," << i.second.hh << endl;
    f.close();
    remove("./data/appointments.csv");
    rename("./data/temp.csv", "./data/appointments.csv");
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
    if (hospital::appointmentsList.size() >= 8 * hospital::doctorsList.size())
    {
        cout << "\n\nSorry, no doctor is available for appointment today!\n\n";
        return;
    }
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
    if (hospital::appointmentsList.rbegin() != hospital::appointmentsList.rend())
        id = ((hospital::appointmentsList.rbegin())->first) + 1;
    else
        id = 1;
    hh = 9 + D.appointmentsBooked;
    hospital::appointmentsList[id] = *this;

    hospital::doctorsList[D.id].appointmentsBooked++;
    cout << "\nAppointment of patient " + P.firstName + " " + P.lastName + " with doctor "
         << D.firstName << " " << D.lastName << " booked successfully!\n";
    printDetails();
    return;
}
void appointment::getDetails()
{
    cout << "\nEnter appointment ID:\n";
    cin >> id;
    if (hospital::appointmentsList.find(id) == hospital::appointmentsList.end())
    {
        cout << "\nInvalid appointment ID!\n";
        id = -1;
        return;
    }
    *this = hospital::appointmentsList[id];
    return;
}