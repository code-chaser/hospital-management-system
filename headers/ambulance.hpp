#ifndef AMBULANCE
#define AMBULANCE
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./person.hpp"
class ambulance
{
protected:
    int id;
    string model;
    string manufacturer;
    string vrn; //vehicle registration number;
    bool idle;
    address add;
    int driverId;

public:
    ambulance()
    {
        id = -1;
        add.strToAdd("`````");
        driverId = -1;
    }
    void addAmbulance()
    {
        //getting the basic details of the ambulance from the user side;
        cout << "\nEnter Model of the ambulance:\n";
        getline(cin >> ws, model);
        cout << "\nEnter Manufacturer Name of the ambulance:\n";
        getline(cin >> ws, manufacturer);
        cout << "\nEnter Vehicle Registration Number of the ambulance:\n";
        getline(cin >> ws, vrn);
        //creating a fstream object to read/write from/to files;
        fstream f;
        //opening the file to read it;
        f.open("./data/ambulances.csv", ios::in);
        //reading the file till the last line to get the id of the last line;
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
        f.open("./data/ambulances.csv", ios::app);
        f << id << "," << model << "," << manufacturer << "," << vrn << ",Y,NA,NA" << endl;
        f.close();

        //creating a record in doctorsHistory.csv;
        f.open("./data/ambulancesHistory.csv", ios::app);
        f << model << "," << manufacturer << "," << vrn << ",Y" << endl;
        f.close();

        cout << "\n"
             << model << " by " << manufacturer << " added successfully!\n";
        cout << "Its ID is: " << id << "\n";
    }
    void printDetails()
    {
        if (id == -1)
            return;
        cout << "Details:\n";
        cout << "ID              : " << id << "\n";
        cout << "Manufacturer    : " << manufacturer << "\n";
        cout << "Model           : " << model << "\n";
        cout << "Reg Number      : " << vrn << "\n";
        cout << "Idle?           : " << ((idle) ? "Y" : "N") << "\n";
        if (!idle)
        {
            cout << "Going to Address: ";
            add.print();
            cout << "Driver ID       : " << driverId << "\n";
        }
        return;
    }
    void printDetailsFromHistory(string extraDetails = "")
    {
        if (id == -1)
            return;
        if (extraDetails == "")
        {
            fstream f;
            f.open("./data/driversHistory.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                ambulance a;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s4;
                //reading from the string stream object 's';
                getline(s, a.model, ',');
                getline(s, a.manufacturer, ',');
                getline(s, s4, ',');

                if (vrn == s4)
                {
                    getline(s, extraDetails, ',');
                }
            }
            f.close();
        }
        cout << "Model           : " << model << "\n";
        cout << "Manufacturer    : " << manufacturer << "\n";
        cout << "Reg. Number     : " << vrn << "\n";
        cout << "Still owned?    : " << extraDetails << "\n";
        return;
    }
    void getDetails(int rec = 0)
    {
        int opt = 0;
        cout << "\nOPTIONS:\n[1]: Filter by ID\n[2]: Filter by Model\n[3]: Filter by Vehicle Reg. Number\n\n";
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
            f.open("./data/ambulances.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s1, s5, s6, s7;
                //reading from the string stream object 's';
                getline(s, s1, ',');

                if (reqId == strToNum(s1))
                {
                    getline(s, model, ',');
                    getline(s, manufacturer, ',');
                    getline(s, vrn, ',');
                    getline(s, s5, ',');
                    getline(s, s6, ',');
                    getline(s, s7, ',');
                    id = reqId;
                    idle = (s5 == "Y");
                    if (!idle)
                        add.strToAdd(s6), driverId = strToNum(s7);
                    return;
                }
            }
            f.close();
            //if a record is found, it's details will be stored in the ambulance class object that called this function,
            //and the control is returned;
            //else:
            cout << "\nNo matching record found!\n";
        }
        //2: Filter by model;
        else if (opt == 2)
        {
            string reqModel;
            cout << "Model:\n";
            getline(cin >> ws, reqModel);
            vector<ambulance> matchingRecords;
            fstream f;
            f.open("./data/ambulances.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                ambulance a;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s1, s5, s6, s7;
                //reading from the string stream object 's';
                getline(s, s1, ',');
                getline(s, a.model, ',');
                getline(s, a.manufacturer, ',');

                if (a.model == reqModel)
                {
                    getline(s, vrn, ',');
                    getline(s, s5, ',');
                    getline(s, s6, ',');
                    getline(s, s7, ',');
                    a.id = strToNum(s1);
                    a.idle = (s5 == "Y");
                    if (!idle)
                        add.strToAdd(s6), driverId = strToNum(s7);
                    matchingRecords.push_back(a);
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
                    cout << "\nEnter the ID of the required ambulance: ";
                    cin >> reqId;
                    for (auto i : matchingRecords)
                        if (reqId == i.id)
                        {
                            id = i.id;
                            model = i.model;
                            manufacturer = i.manufacturer;
                            vrn = i.vrn;
                            idle = i.idle;
                            add = i.add;
                            driverId = i.driverId;
                            return;
                        }
                    cout << "\nInvalid ID!\nTry again? (Y = Yes || N = No)\n";
                    cin >> tt;
                    while (tt != 'Y' || tt != 'N')
                        cout << "Y or N?\n", cin >> tt;
                } while (tt == 'Y');
            }
        }
        //3: Filter by vehicle reg. number;
        else if (opt == 3)
        {
            string reqVRN;
            cout << "Enter the vehicle reg. number of ambulance required:\n";
            getline(cin >> ws, reqVRN);
            fstream f;
            f.open("./data/ambulances.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s1, s5, s6, s7;
                //reading from the string stream object 's';
                getline(s, s1, ',');
                getline(s, model, ',');
                getline(s, manufacturer, ',');
                getline(s, vrn, ',');
                if (vrn == reqVRN)
                {
                    getline(s, s5, ',');
                    getline(s, s6, ',');
                    getline(s, s7, ',');
                    id = strToNum(s1);
                    idle = (s5 == "Y");
                    if (!idle)
                        add.strToAdd(s6), driverId = strToNum(s7);

                    return;
                }
            }
            f.close();
            //if a record is found, it's details will be stored in the ambulance class object that called this function,
            //and the control is returned;
            //else:
            cout << "\nNo matching record found!\n";
        }
        return;
    }
    void getDetailsFromHistory()
    {
        int opt = 0;
        cout << "\nOPTIONS:\n[1]: Filter by model\n[2]: Filter by vehicle reg. number\n\n";
        cin >> opt;
        while (opt != 1 && opt != 2)
            cout << "option 1 or 2?\n", cin >> opt;

        //1: Filter by name;
        if (opt == 1)
        {
            string reqModel;
            cout << "Model:\n";
            getline(cin >> ws, reqModel);
            vector<ambulance> matchingRecords;
            vector<string> extraDetails;
            fstream f;
            f.open("./data/ambulancesHistory.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                ambulance a;
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s4;
                bool owned;
                //reading from the string stream object 's';
                getline(s, a.model, ',');

                if (a.model == reqModel)
                {

                    getline(s, a.manufacturer, ',');
                    getline(s, vrn, ',');
                    getline(s, s4, ',');
                    a.id = 0;
                    matchingRecords.push_back(a);
                    extraDetails.push_back(s4);
                }
            }
            f.close();
            cout << "\n";
            cout << matchingRecords.size() << " matching record(s) found!\n";
            for (int i = 0; i < matchingRecords.size(); i++)
                matchingRecords[i].printDetailsFromHistory(extraDetails[i]);
        }
        //2: Filter by vrn;
        else if (opt == 2)
        {
            string reqVRN;
            cout << "Enter the vehicle reg. number of ambulance required:\n";
            getline(cin >> ws, reqVRN);
            vector<ambulance> matchingRecords;
            vector<string> extraDetails;
            fstream f;
            f.open("./data/ambulancesHistory.csv", ios::in);
            string temp;
            //skipping the first row containing column headers;
            getline(f >> ws, temp);
            //analyzing each entry afterwards;
            while (getline(f >> ws, temp))
            {
                //creating a string stream object to read from string 'temp';
                stringstream s(temp);
                string s4;
                //reading from the string stream object 's';
                getline(s, model, ',');
                getline(s, manufacturer, ',');
                getline(s, vrn, ',');
                if (vrn == reqVRN)
                {
                    getline(s, s4, ',');
                    id = 0;
                    printDetailsFromHistory(s4);
                    return;
                }
            }
            f.close();
            //if a record is found, it's details will be stored in the ambulance class object that called this function,
            //and the control is returned;
            //else:
            cout << "\nNo matching record found!\n";
        }
        return;
    }
    void send()
    {

        //*************picking an idle ambulance*************;

        bool gotOne = 0;
        fstream f, fout;
        f.open("./data/ambulances.csv", ios::in);
        string temp;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s1, s5, s6, s7;
            //reading from the string stream object 's';
            getline(s, s1, ',');
            getline(s, model, ',');
            getline(s, manufacturer, ',');
            getline(s, vrn, ',');
            getline(s, s5, ',');
            if (s5 == "Y")
            {
                getline(s, s6, ',');
                getline(s, s7, ',');
                id = strToNum(s1);
                idle = 1;
                gotOne = 1;
                break;
            }
        }
        f.close();
        if (!gotOne)
        {
            cout << "No, idle ambulance found!"
                 << "\n";
            return;
        }
        //*************  picking a free driver  *************;

        gotOne=0;
        f.open("./data/drivers.csv", ios::in);
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            string s1, s2, s9;
            //reading from the string stream object 's';
            getline(s, s1, ',');
            getline(s, s2, ',');
            getline(s, s2, ',');
            getline(s, s2, ',');
            getline(s, s2, ',');
            getline(s, s2, ',');
            getline(s, s2, ',');
            getline(s, s2, ',');
            getline(s, s9, ',');

            if (s9 == "Y")
            {
                driverId = strToNum(s1);
                gotOne=1;
                break;
            }
        }
        f.close();
        if (!gotOne)
        {
            cout << "No, idle driver found!"
                 << "\n";
            return;
        }

        cout << "Enter destination address:\n";
        add.takeInput();

        //updating status of ambulance;
        string initial, corrected;
        stringstream str;
        str << id << "," << model << "," << manufacturer
            << "," << vrn << ",Y,NA,NA\n";
        getline(str >> ws, initial);
        str << id << "," << model << "," << manufacturer
            << "," << vrn << ","
            << "N"
            << "," << add.addToStr() << "," << driverId << "\n";
        getline(str >> ws, corrected);
        f.open("./data/ambulances.csv", ios::in);
        fout.open("./data/temp.csv", ios::out);
        while (getline(f, temp))
        {
            if (temp != initial)
                fout << temp << endl;
            else
                fout << corrected << endl;
        }
        f.close();
        fout.close();
        initial.erase();
        temp.erase();
        remove("./data/ambulances.csv");
        rename("./data/temp.csv", "./data/ambulances.csv");

        //updating status of driver;
        f.open("./data/drivers.csv", ios::in);

        string s1, s2, s3, s4, s5, s6, s7, s8, s9;
        //skipping the first row containing column headers;
        getline(f >> ws, temp);
        //analyzing each entry afterwards;
        while (getline(f >> ws, temp))
        {
            //creating a string stream object to read from string 'temp';
            stringstream s(temp);
            //reading from the string stream object 's';
            getline(s, s1, ',');

            if (driverId == strToNum(s1))
            {
                getline(s, s2, ',');
                getline(s, s3, ',');
                getline(s, s4, ',');
                getline(s, s5, ',');
                getline(s, s6, ',');
                getline(s, s7, ',');
                getline(s, s8, ',');
                getline(s, s9, ',');
                break;
            }
        }
        f.close();
        initial = s1 + "," + s2 + "," + s3 + "," + s4 + "," + s5 + "," + s6 + "," + s7 + "," + s8 + "," + s9;
        corrected = s1 + "," + s2 + "," + s3 + "," + s4 + "," + s5 + "," + s6 + "," + s7 + "," + s8 + ",N";
        fout.open("./data/temp.csv", ios::out);
        f.open("./data/drivers.csv", ios::in);
        while (getline(f, temp))
        {
            if (temp != initial)
                fout << temp << "\n";
            else
                fout << corrected << "\n";
        }
        f.close();
        fout.close();
        initial.erase();
        temp.erase();
        remove("./data/drivers.csv");
        rename("./data/temp.csv", "./data/drivers.csv");
        cout << model << " by " << manufacturer << " sent with driver " << s2 << " " << s3 << " (ID = " << s1 << ") successfully!\n";
        return;
    }
    void reportArrival()
    {
    }
    void removeAmbulance()
    {
    }
};
#endif // !AMBULANCE