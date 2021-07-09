#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ios>    //used to get stream size
#include <limits> //used to get numeric limits
using namespace std;

#include "./include/global.hh"
#include "./include/hospital.hh"
#include "./include/address.hh"
#include "./include/person.hh"
#include "./include/appointment.hh"
#include "./include/patient.hh"
#include "./include/doctor.hh"
#include "./include/nurse.hh"
#include "./include/driver.hh"
#include "./include/ambulance.hh"

int main()
{
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
        cout << "\n\n\nLast usage date (DD-MM-YYYY) : " << s.substr(6, 2) + "-" + s.substr(4, 2) + "-" + s.substr(0, 4) + "\n";
    cout << "\nPlease Enter Today's Date (DD-MM-YYYY) :\n\nEnter Day: ";
    cin >> dd;
    cout << "Enter Month: ";
    cin >> mm;
    cout << "Enter Year (YYYY): ";
    cin >> yyyy;
    yyyymmdd = yyyy * 10000 + mm * 100 + dd;
    if (strToNum(((s == "") ? ("0") : (s))) < yyyymmdd)
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
    else if (strToNum(s) > yyyymmdd && s != "")
    {
        cout << "\nEntered date detected wrong!\nToday's date can't be older than the last usage date, which is : "
             << s.substr(6, 2) + "-" + s.substr(4, 2) + "-" + s.substr(0, 4) + "\n";
        return 0;
    }
    // filling maps with data from csv files;
    {
        doctor d1;
        patient p;
        nurse n;
        driver d2;
        ambulance a1;
        appointment a2;
        d1.fillMap();
        p.fillMap();
        n.fillMap();
        d2.fillMap();
        a1.fillMap();
        a2.fillMap();
        // NOTE:
        // fill drivers' Map before ambulances' Map;
        // fill doctors' and patients' Map before appointments' Map;
    }
    while (1)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect an option:\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        //APPOINTMENTS - RELATED;
        cout << "[01] : Book an appointment\n";
        cout << "[02] : Get appointment details\n";
        cout << "[03] : Show all appointments\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        //PATIENTS - RELATED;
        cout << "[04] : Register a new patient\n";
        cout << "[05] : Get patient details\n";
        cout << "[06] : Hospitalize a registered patient\n";
        cout << "[07] : Report a patient's death\n";
        cout << "[08] : Discharge a patient or their body\n";
        cout << "[09] : Fetch patient details from history\n";
        cout << "[10] : Get details of all registered patients\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        //DOCTORS - RELATED;
        cout << "[11] : Register a new doctor\n";
        cout << "[12] : Get doctor details\n";
        cout << "[13] : Remove a doctor\n";
        cout << "[14] : Fetch doctor details from history\n";
        cout << "[15] : Get details of all registered doctors\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        //NURSES - RELATED;
        cout << "[16] : Register a new nurse\n";
        cout << "[17] : Get nurse details\n";
        cout << "[18] : Remove a nurse\n";
        cout << "[19] : Fetch nurse details from history\n";
        cout << "[20] : Get details of all registered nurses\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        //AMBULANCES - RELATED;
        cout << "[21] : Add an ambulance\n";
        cout << "[22] : Send an ambulance\n";
        cout << "[23] : Get ambulance details\n";
        cout << "[24] : Report ambulance arrival\n";
        cout << "[25] : Remove an ambulance\n";
        cout << "[26] : Fetch ambulance details from history\n";
        cout << "[27] : Get details of all registered ambulances\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        //AMBULANCE DRIVERS - RELATED;
        cout << "[28] : Register a new ambulance driver\n";
        cout << "[29] : Get driver details\n";
        cout << "[30] : Remove a driver\n";
        cout << "[31] : Fetch driver details from history\n";
        cout << "[32] : Get details of all registered drivers\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

        cout << "[-1] : Exit\n";
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cin >> purpose;
        if (purpose == -1)
        {
            cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "\nShutting Down System...\n";
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            break;
        }
        cout << "\n";
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if (purpose == 1)
        {
            appointment a;
            a.book();
        }
        else if (purpose == 2)
        {
            appointment a;
            a.getDetails();
            a.printDetails();
        }
        else if (purpose == 3)
        {
            hospital::printAppointments();
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if (purpose == 4)
        {
            patient p;
            p.addPerson();
        }
        else if (purpose == 5)
        {
            patient p;
            p.getDetails(1);
            p.printDetails();
        }
        else if (purpose == 6)
        {
            patient p;
            p.hospitalize();
        }
        else if (purpose == 7)
        {
            patient p;
            p.reportADeath();
        }
        else if (purpose == 8)
        {
            patient p;
            p.removePerson();
        }
        else if (purpose == 9)
        {
            patient p;
            p.getDetailsFromHistory();
        }
        else if (purpose == 10)
        {
            hospital::printPatients();
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if (purpose == 11)
        {
            doctor d;
            d.addPerson();
        }
        else if (purpose == 12)
        {
            doctor d;
            d.getDetails(1);
            d.printDetails();
        }
        else if (purpose == 13)
        {
            doctor d;
            d.removePerson();
        }
        else if (purpose == 14)
        {
            doctor d;
            d.getDetailsFromHistory();
        }
        else if (purpose == 15)
        {
            hospital::printDoctors();
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if (purpose == 16)
        {
            nurse n;
            n.addPerson();
        }
        else if (purpose == 17)
        {
            nurse n;
            n.getDetails(1);
            n.printDetails();
        }
        else if (purpose == 18)
        {
            nurse n;
            n.removePerson();
        }
        else if (purpose == 19)
        {
            nurse n;
            n.getDetailsFromHistory();
        }
        else if (purpose == 20)
        {
            hospital::printNurses();
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if (purpose == 21)
        {
            ambulance a;
            a.addAmbulance();
        }
        else if (purpose == 22)
        {
            ambulance a;
            a.send();
        }
        else if (purpose == 23)
        {
            ambulance a;
            a.getDetails(1);
            a.printDetails();
        }
        else if (purpose == 24)
        {
            ambulance a;
            a.reportArrival();
        }
        else if (purpose == 25)
        {
            ambulance a;
            a.removeAmbulance();
        }
        else if (purpose == 26)
        {
            ambulance a;
            a.getDetailsFromHistory();
        }
        else if (purpose == 27)
        {
            hospital::printAmbulances();
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if (purpose == 28)
        {
            driver d;
            d.addPerson();
        }
        else if (purpose == 29)
        {
            driver d;
            d.getDetails(1);
            d.printDetails();
        }
        else if (purpose == 30)
        {
            driver d;
            d.removePerson();
        }
        else if (purpose == 31)
        {
            driver d;
            d.getDetailsFromHistory();
        }
        else if (purpose == 32)
        {
            hospital::printDrivers();
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else
        {
            cout << "\nInvalid Choice!\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing cin buffer;

        cout << endl;
        cout << "\nPress ENTER to continue...\n";
        cout << endl;

        getchar();
    }
    // saving data inside maps by overwriting it on the files
    {
        doctor d1;
        patient p;
        nurse n;
        driver d2;
        ambulance a1;
        appointment a2;
        d1.saveMap();
        p.saveMap();
        n.saveMap();
        d2.saveMap();
        a1.saveMap();
        a2.saveMap();
    }

    return 0;
}
