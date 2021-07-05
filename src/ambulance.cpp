using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./../include/global.hh"
#include "./../include/ambulance.hh"
ambulance::ambulance()
{
    id = -1;
    add.strToAdd("`````");
    d.id = -1;
}
void ambulance::addAmbulance()
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
void ambulance::printDetails()
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
        cout << "Driver ID       : " << d.id << "\n";
    }
    return;
}
void ambulance::printDetailsFromHistory(string extraDetails)
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
void ambulance::getDetails(int rec)
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
                f.close();
                getline(s, model, ',');
                getline(s, manufacturer, ',');
                getline(s, vrn, ',');
                getline(s, s5, ',');
                getline(s, s6, ',');
                getline(s, s7, ',');
                id = reqId;
                idle = (s5 == "Y");
                if (!idle)
                {
                    add.strToAdd(s6);
                    d.id = strToNum(s7);
                    f.open("./data/drivers.csv", ios::in);
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

                        if (d.id == strToNum(s1))
                        {
                            f.close();
                            getline(s, d.firstName, ',');
                            getline(s, d.lastName, ',');
                            getline(s, s4, ',');
                            getline(s, s5, ',');
                            getline(s, d.mobNumber, ',');
                            getline(s, s7, ',');
                            getline(s, d.licenseNumber, ',');
                            getline(s, s9, ',');
                            d.gender = s4[0];
                            d.age = strToNum(s5);
                            d.add.strToAdd(s7);
                            d.idle = (s9 == "Y");
                        }
                    }
                }
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
                getline(s, a.vrn, ',');
                getline(s, s5, ',');
                getline(s, s6, ',');
                getline(s, s7, ',');
                a.id = strToNum(s1);
                a.idle = (s5 == "Y");
                if (!a.idle)
                {
                    a.add.strToAdd(s6);
                    a.d.id = strToNum(s7);
                    fstream f;
                    f.open("./data/drivers.csv", ios::in);
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

                        if (a.d.id == strToNum(s1))
                        {
                            f.close();
                            getline(s, a.d.firstName, ',');
                            getline(s, a.d.lastName, ',');
                            getline(s, s4, ',');
                            getline(s, s5, ',');
                            getline(s, a.d.mobNumber, ',');
                            getline(s, s7, ',');
                            getline(s, a.d.licenseNumber, ',');
                            getline(s, s9, ',');
                            a.d.gender = s4[0];
                            a.d.age = strToNum(s5);
                            a.d.add.strToAdd(s7);
                            a.d.idle = (s9 == "Y");
                        }
                    }
                }
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
                        d.id = i.d.id;
                        d.firstName = i.d.firstName;
                        d.lastName = i.d.lastName;
                        d.gender = i.d.gender;
                        d.age = i.d.age;
                        d.mobNumber = i.d.mobNumber;
                        d.add = i.d.add;
                        d.licenseNumber = i.d.licenseNumber;
                        d.idle = i.d.idle;
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
                f.close();
                getline(s, s5, ',');
                getline(s, s6, ',');
                getline(s, s7, ',');
                id = strToNum(s1);
                idle = (s5 == "Y");
                if (!idle)
                {
                    add.strToAdd(s6);
                    d.id = strToNum(s7);
                    f.open("./data/drivers.csv", ios::in);
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

                        if (d.id == strToNum(s1))
                        {
                            f.close();
                            getline(s, d.firstName, ',');
                            getline(s, d.lastName, ',');
                            getline(s, s4, ',');
                            getline(s, s5, ',');
                            getline(s, d.mobNumber, ',');
                            getline(s, s7, ',');
                            getline(s, d.licenseNumber, ',');
                            getline(s, s9, ',');
                            d.gender = s4[0];
                            d.age = strToNum(s5);
                            d.add.strToAdd(s7);
                            d.idle = (s9 == "Y");
                        }
                    }
                }

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
void ambulance::getDetailsFromHistory()
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
                getline(s, a.vrn, ',');
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
void ambulance::send()
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

    gotOne = 0;
    f.open("./data/drivers.csv", ios::in);
    //skipping the first row containing column headers;
    getline(f >> ws, temp);
    //analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        //creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string s1, s2, s3, s4, s5, s6, s7, s8, s9;
        //reading from the string stream object 's';
        getline(s, s1, ',');
        getline(s, d.firstName, ',');
        getline(s, d.lastName, ',');
        getline(s, s4, ',');
        getline(s, s5, ',');
        getline(s, d.mobNumber, ',');
        getline(s, s7, ',');
        getline(s, d.licenseNumber, ',');
        getline(s, s9, ',');

        if (s9 == "Y")
        {
            d.id = strToNum(s1);
            d.gender = s4[0];
            d.age = strToNum(s5);
            d.add.strToAdd(s7);
            d.idle = 0;
            gotOne = 1;
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
        << "," << add.addToStr() << "," << d.id << "\n";
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

        if (d.id == strToNum(s1))
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
    str << d.id << "," << d.firstName << "," << d.lastName << "," << d.gender
        << "," << d.age << "," << d.mobNumber << "," << d.add.addToStr()
        << "," << d.licenseNumber << ",N\n";
    getline(str >> ws, corrected);
    str << d.id << "," << d.firstName << "," << d.lastName << "," << d.gender
        << "," << d.age << "," << d.mobNumber << "," << d.add.addToStr()
        << "," << d.licenseNumber << ",Y\n";
    getline(str >> ws, initial);
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
void ambulance::reportArrival()
{
    getDetails();
    //updating status of ambulance;
    string initial, corrected, temp;
    stringstream str;
    str << id << "," << model << "," << manufacturer
        << "," << vrn << ",Y,NA,NA\n";
    getline(str >> ws, corrected);

    str << id << "," << model << "," << manufacturer
        << "," << vrn << ","
        << "N"
        << "," << add.addToStr() << "," << d.id << "\n";
    getline(str >> ws, initial);
    fstream f, fout;
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
    str << d.id << "," << d.firstName << "," << d.lastName << "," << d.gender
        << "," << d.age << "," << d.mobNumber << "," << d.add.addToStr()
        << "," << d.licenseNumber << ",N\n";
    getline(str >> ws, initial);
    str << d.id << "," << d.firstName << "," << d.lastName << "," << d.gender
        << "," << d.age << "," << d.mobNumber << "," << d.add.addToStr()
        << "," << d.licenseNumber << ",Y\n";
    getline(str >> ws, corrected);
    f.open("./data/drivers.csv", ios::in);
    fout.open("./data/temp.csv", ios::out);
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
    cout << "\nStatus of " << model << " by " << manufacturer << " sent with driver " << d.firstName << " " << d.lastName << " (ID = " << d.id << ") updated successfully!\n\n";
    return;
}
void ambulance::removeAmbulance()
{
    cout << "\nSearch for the ambulance you want to remove.\n";
    getDetails();
    if (id == -1)
        return;
    if (!idle)
    {
        cout << "\nSorry, the ambulance you selected to remove is NOT currently idle.\nOnly idlers can be removed.\n\n";
        return;
    }
    string s, temp;
    stringstream str(s);
    str << id << "," << model << "," << manufacturer << "," << vrn << ",Y,NA,NA\n";
    getline(str, s);
    fstream f, fout("./data/temp.csv", ios::out);
    f.open("./data/ambulances.csv", ios::in);
    while (getline(f, temp))
        if (temp != s)
            fout << temp << "\n";
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("./data/ambulances.csv");
    rename("./data/temp.csv", "./data/ambulances.csv");
    str << model << "," << manufacturer << "," << vrn << ",Y\n";
    getline(str, s);
    f.open("./data/ambulancesHistory.csv", ios::in);
    fout.open("./data/temp.csv", ios::out);
    while (getline(f, temp))
    {
        if (temp == s)
        {
            fout << model << "," << manufacturer << "," << vrn << ",N,"
                 << "\n";
        }
        else
            fout << temp << "\n";
    }
    f.close();
    fout.close();
    s.erase();
    temp.erase();
    remove("./data/ambulancesHistory.csv");
    rename("./data/temp.csv", "./data/ambulancesHistory.csv");
    cout << model << " by " << manufacturer << " (VRN = " << vrn << ") removed successfully!\n";
    return;
}
