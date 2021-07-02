#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;
int power(int n, int exp)
{
    int res = 1;
    while (exp)
    {
        if (exp & 1)
            res *= n, exp--;
        else
            n *= n, exp >>= 1;
    }
    return res;
}
int strToNum(string s)
{
    int res = 0;
    for (int i = 0; i < s.size(); i++)
        res += ((s[s.size() - 1 - i] - '0') * power(10, i));
    return res;
}

#include "./headers/address.hpp"
#include "./headers/person.hpp"
#include "./headers/appointment.hpp"
#include "./headers/patient.hpp"
#include "./headers/doctor.hpp"
#include "./headers/nurse.hpp"
#include "./headers/driver.hpp"
#include "./headers/ambulance.hpp"

int main()
{
    while (1)
    {
        int purpose = 0;
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\nSelect an option:\n\n";
        
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        
        cout << "[01] : Book an appointment\n";
        cout << "[02] : Check appointment status\n";
        cout << "[03] : Update appointment status\n";
        cout << "[04] : Cancel an appointment\n\n";

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

        cout << "[05] : Register a new patient\n";
        cout << "[06] : Get patient details\n";
        cout << "[07] : Hospitalize a registered patient\n";
        cout << "[08] : Report a patient's death\n";
        cout << "[09] : Discharge a patient or their body\n";
        cout << "[10] : Fetch patient details from history\n\n";
        
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

        cout << "[11] : Register a new doctor\n";
        cout << "[12] : Get doctor details\n";
        cout << "[13] : Remove a doctor\n";
        cout << "[14] : Fetch doctor details from history\n\n";
        
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

        cout << "[15] : Register a new nurse\n";
        cout << "[16] : Get nurse details\n";
        cout << "[17] : Remove a nurse\n";
        cout << "[18] : Fetch nurse details from history\n\n";
        
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

        cout << "[19] : Add an ambulance\n";
        cout << "[20] : Send an ambulance\n";
        cout << "[21] : Get ambulance details\n";
        cout << "[22] : Report ambulance arrival\n";
        cout << "[23] : Remove an ambulance\n";
        cout << "[24] : Fetch ambulance details from history\n\n";
        
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

        cout << "[25] : Register a new ambulance driver\n";
        cout << "[26] : Get driver details\n";
        cout << "[27] : Remove a driver\n";
        cout << "[28] : Fetch driver details from history\n\n";
        
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

        cout << "[-1] : Exit\n";
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
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
            patient p;
            p.addPerson();
        }
        else if (purpose == 6)
        {
            patient p;
            p.getDetails();
            p.printDetails();
        }
        else if (purpose == 7)
        {
            patient p;
            p.hospitalize();
        }
        else if (purpose == 8)
        {
            patient p;
            p.reportADeath();
        }
        else if (purpose == 9)
        {
            patient p;
            p.removePerson();
        }
        else if (purpose == 10)
        {
            patient p;
            p.getDetailsFromHistory();
        }
        else if (purpose == 11)
        {
            doctor d;
            d.addPerson();
        }
        else if (purpose == 12)
        {
            doctor d;
            d.getDetails();
            d.printDetails();
        }
        else if (purpose == 13)
        {
            doctor d;
            d.removePerson();
            d.printDetailsFromHistory();
        }
        else if (purpose == 14)
        {
            doctor d;
            d.getDetailsFromHistory();
        }
        else if (purpose == 15)
        {
            nurse n;
            n.addPerson();
        }
        else if (purpose == 16)
        {
            nurse n;
            n.getDetails();
            n.printDetails();
        }
        else if (purpose == 17)
        {
            nurse n;
            n.removePerson();
            n.printDetailsFromHistory();
        }
        else if (purpose == 18)
        {
            nurse n;
            n.getDetailsFromHistory();
        }
        else if (purpose == 19)
        {
            ambulance a;
            a.addAmbulance();
        }
        else if (purpose == 20)
        {
            ambulance a;
            a.send();
        }
        else if (purpose == 21)
        {
            ambulance a;
            a.getDetails();
            a.printDetails();
        }
        else if (purpose == 22)
        {
        }
        else if (purpose == 23)
        {
        }
        else if (purpose == 24)
        {
            ambulance a;
            a.getDetailsFromHistory();
        }
        else if (purpose == 25)
        {
            driver d;
            d.addPerson();
        }
        else if (purpose == 26)
        {
            driver d;
            d.getDetails();
            d.printDetails();
        }
        else if (purpose == 27)
        {
            driver d;
            d.removePerson();
            d.printDetailsFromHistory();
        }
        else if (purpose == 28)
        {
            driver d;
            d.getDetailsFromHistory();
        }
        else
        {
            cout << "\nInvalid Choice!\n";
        }
    }
    return 0;
}
