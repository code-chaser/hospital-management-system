#ifndef NURSE
#define NURSE
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./person.hpp"
class nurse : public person
{
private:
public:
    nurse()
    {
        id = -1;
        cat = "nurse";
        category = 3;
    }
    void addANurse()
    {
        //getting the basic details of nurse from the user side;
        setDetails();
        //creating a fstream object to read/write from/to files;
        fstream f;
        //opening the file to read it;
        f.open("./data/nurses.csv", ios::in);
        //reading the file till the last line to get the id of the last line;
        string temp, idString = "";
        while (getline(f >> ws, temp))
            ;
        f.close();
        stringstream s(temp);
        getline(s, idString, ',');
        id = strToNum(idString) + 1;
        temp.erase();
        idString.erase();
        //creating a record in nurses.csv;
        f.open("./data/nurses.csv", ios::app);
        f << id << "," << firstName << "," << lastName << "," << gender << "," << age << "," << mobNumber << "," << address << endl;
        f.close();

        //creating a record in patientsHistory.csv;
        f.open("./data/patientsHistory.csv", ios::app);
        f << firstName << "," << lastName << "," << gender << "," << age << "," << mobNumber << "," << address << ",No,NA" << endl;
        f.close();

        cout << "\n"
             << firstName << " " << lastName << " added successfully!\n";
        cout << "Their ID is: " << id << "\n";

        return;
    }
};
#endif // !NURSE