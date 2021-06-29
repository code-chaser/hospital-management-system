#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;
int strToNum(string s)
{
    int n = s.size(), res = 0;
    while (n--)
        res += (s[s.size() - 1 - n] - '0') * pow(10, n);
    return res;
}
#include "./headers/person.hpp"
#include "./headers/appointment.hpp"
#include "./headers/patient.hpp"
#include "./headers/doctor.hpp"
#include "./headers/nurse.hpp"
#include "./headers/ambulance.hpp"
#include "./headers/driver.hpp"

int main()
{
    while (1)
    {
        int purpose = 0;
        cout << "\nSelect an option:\n\n";
        cout << "[01] : Book an appointment\n";
        cout << "[02] : Check appointment status\n";
        cout << "[03] : Update appointment status\n";
        cout << "[04] : Cancel an appointment\n\n";

        cout << "[05] : Register a new patient\n";
        cout << "[05] : Get patient details\n";
        cout << "[06] : Hospitalize a patient\n";
        cout << "[07] : Report a patient's death\n";
        cout << "[08] : Discharge a patient (alive)\n";
        cout << "[09] : Fetch patient details from history\n\n";

        cout << "[10] : Register a new doctor\n";
        cout << "[11] : Get doctor details\n";
        cout << "[12] : Remove a doctor\n";
        cout << "[13] : Fetch doctor details from history\n\n";

        cout << "[14] : Register a new nurse\n";
        cout << "[15] : Get nurse details\n";
        cout << "[16] : Remove a nurse\n";
        cout << "[17] : Fetch nurse details from history\n\n";

        cout << "[18] : Add an ambulance\n";
        cout << "[19] : Send an ambulance\n";
        cout << "[20] : Check ambulance status\n";
        cout << "[21] : Remove an ambulance\n";
        cout << "[22] : Fetch ambulance details from history\n\n";

        cout << "[23] : Register a new ambulance driver\n";
        cout << "[24] : Get driver details\n";
        cout << "[25] : Remove a driver\n";
        cout << "[26] : Fetch driver details from history\n\n";

        cout << "[-1] : Exit\n";
        cin >> purpose;
        if (purpose == -1)
        {
            cout << "\n\nShutting Down System...\n\n";
            return 0;
        }
        if (purpose == 1)
        {
            patient p;
            p.addAPatient();
            p.printDetails();
        }
        else if (purpose == 2)
        {
        }
        else if (purpose == 3)
        {
        }
        else if (purpose == 4)
        {
        }
        else if (purpose == 5)
        {
        }
        else if (purpose == 6)
        {
        }
        else if (purpose == 7)
        {
        }
        else if (purpose == 8)
        {
        }
        else if (purpose == 9)
        {
        }
        else if (purpose == 10)
        {
            doctor d;
            d.addADoctor();
        }
        else if (purpose == 11)
        {
            doctor d;
            d.getADoctor();
            d.printDetails();
        }
        else if (purpose == 12)
        {
            doctor d;
            d.removeADoctor();
            d.printHistoryDetails();
        }
        else if (purpose == 13)
        {
            doctor d;
            d.getADoctorFromHistory();
        }
        else
        {
            cout << "\nInvalid Choice!\n";
        }
    }
    return 0;
}
