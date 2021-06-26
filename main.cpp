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
#include "./headers/doctor.hpp"
#include "./headers/patient.hpp"

int main()
{
    while (1)
    {
        int purpose = 0;
        cout << "\nSelect an option:\n\n";
        cout << "[01] : Book an appointment\n";
        cout << "[02] : Check appointment status\n";
        cout << "[03] : Cancel an appointment\n";
        cout << "[04] : Add a patient\n";
        cout << "[05] : Hospitalize a patient\n";
        cout << "[06] : Remove a patient\n";
        cout << "[07] : Add a doctor\n";
        cout << "[08] : Get doctor details\n";
        cout << "[09] : Fetch doctor details from history\n";
        cout << "[10] : Send an ambulance\n";
        cout << "[11] : Add an ambulance\n";
        cout << "[12] : Get ambulance details\n";
        cout << "[13] : \n";
        cout << "[-1] : Exit\n";
        cin >> purpose;
        if (purpose == -1)
        {
            cout << "Shutting Down System...\n\n";
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
