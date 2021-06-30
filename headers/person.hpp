#ifndef PERSON
#define PERSON
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
class person
{
protected:
    int id = -2;
    string firstName, lastName;
    char gender;
    int16_t age = 0;
    string mobNumber;
    string address;
    string cat = "";
    int category = 0;
    //category: 1:doctor; 2:patient; 3:nurse; 4:driver;

public:
    void setDetails(int16_t minAge = 0, int16_t maxAge = 1000)
    {
        //getting basic details of the person from the user side;
        cout << "\nEnter name: \nFirst Name:\n";
        getline(cin >> ws, firstName);
        cout << "\nLast name:\n";
        getline(cin >> ws, lastName);

        cout << "\nEnter age: \n";
        cin >> age;
        while (age <= 0)
            cout << "Was that supposed to make any kind of sense?\nEnter again!\n", cin >> age;
        if (category != 2)
        {
            if (age < minAge)
                return void(cout << "Sorry, person should be at least " << minAge << " years old to be registered as a " << cat << ".\n");
            else if (age > maxAge)
                return void(cout << "Sorry, we can't register a person older than " << maxAge << " years as a " << cat << ".\n");
        }

        cout << "\nGender (M = Male || F = Female): \n";
        cin >> gender;
        while (gender != 'M' && gender != 'F')
            cout << "M or F?\n", cin >> gender;
        cout << "\nEnter mobile number (with country code): \n";
        getline(cin >> ws, mobNumber);
        cout << "\nEnter residential address (enter in one line): \n";
        getline(cin >> ws, address);
        for (auto &i : address)
            if (i == ',')
                i = '`';
        return;
    }
    void printPersonDetails()
    {
        if (id == -1)
            return;
        cout << "\nDeatils :\n";
        cout << "ID              : " << id << "\n";
        cout << "Full Name       : " << firstName << " " << lastName << "\n";
        cout << "Gender          : " << gender << "\n";
        cout << "Age             : " << age << "\n";
        cout << "Mobile          : " << mobNumber << "\n";
        cout << "Address         : ";
        for (auto i : address)
        {
            if (i == '`')
                cout << ',';
            else
                cout << i;
        }
        cout << "\n";
        return;
    }
    void printPersonHistoryDetails()
    {
        if (id == -1)
            return;
        cout << "\nHistory Deatils :\n";
        cout << "Full Name       : " << firstName << " " << lastName << "\n";
        cout << "Gender          : " << gender << "\n";
        cout << "Age             : " << age << "\n";
        cout << "Mobile          : " << mobNumber << "\n";
        cout << "Address         : ";
        for (auto i : address)
        {
            if (i == '`')
                cout << ',';
            else
                cout << i;
        }
        cout << "\n";
        return;
    }
};
#endif // !PERSON