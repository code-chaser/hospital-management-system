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
        cout << "[03] : Cancel an appointment\n\n";

        cout << "[04] : Get patient details\n";
        cout << "[05] : Hospitalize a patient\n";
        cout << "[06] : Remove a patient\n";
        cout << "[07] : Fetch patient details from history\n\n";

        cout << "[08] : Register a new doctor\n";
        cout << "[09] : Get doctor details\n";
        cout << "[10] : Remove a doctor\n";
        cout << "[11] : Fetch doctor details from history\n\n";

        cout << "[12] : Register a new nurse\n";
        cout << "[13] : Get nurse details\n";
        cout << "[14] : Remove a nurse\n";
        cout << "[15] : Fetch nurse details from history\n\n";

        cout << "[16] : Add an ambulance\n";
        cout << "[17] : Send an ambulance\n";
        cout << "[18] : Check ambulance status\n";
        cout << "[19] : Remove an ambulance\n\n";
        cout << "[20] : Fetch ambulance details from history\n\n";
        
        cout << "[21] : Register a new ambulance driver\n";
        cout << "[22] : Get driver details\n";
        cout << "[23] : Remove a driver\n";
        cout << "[24] : Fetch driver details from history\n";

        cout << "[-1] : Exit\n";
        cin >> purpose;
        if (purpose == -1)
        {
            cout << "\n\nShutting Down System...\n\n";
            return 0;
        }
        if (purpose == 1)
        {
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
            doctor d;
            d.addADoctor();
        }
        else if (purpose == 8)
        {
            doctor d;
            d.getADoctor();
            d.printDetails();
        }
        else if (purpose == 9)
        {
        }
        else if (purpose == 10)
        {
        }
        else if (purpose == 11)
        {
        }
        else if (purpose == 12)
        {
        }
        else if (purpose == 13)
        {
        }
        else
        {
            cout << "\nInvalid Choice!\n";
        }
    }
    return 0;
}
