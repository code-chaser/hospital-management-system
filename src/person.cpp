using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "./../include/global.hh"
#include "./../include/person.hh"

person::person()
{
    id = -1;
}
void person::addPerson(int16_t minAge, int16_t maxAge)
{
    //getting basic details of the person from the user side;
    cout << "\nEnter name: \nFirst name:\n";
    getline(cin >> ws, firstName);
    cout << "\nLast name:\n";
    getline(cin, lastName);

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
    add.takeInput();
    return;
}
void person::printDetails()
{
    if (id == -1)
        return;
    cout << "\nDetails:\n";
    cout << "ID              : " << id << "\n";
    cout << "Full Name       : " << firstName << " " << lastName << "\n";
    cout << "Gender          : " << gender << "\n";
    cout << "Age             : " << age << "\n";
    cout << "Mobile          : " << mobNumber << "\n";
    cout << "Address         : ";
    add.print();
    return;
}
void person::printDetailsFromHistory()
{
    if (id == -1)
        return;
    cout << "\nHistory Details :\n";
    cout << "Full Name       : " << firstName << " " << lastName << "\n";
    cout << "Gender          : " << gender << "\n";
    cout << "Age             : " << age << "\n";
    cout << "Mobile          : " << mobNumber << "\n";
    cout << "Address         : ";
    add.print();
    return;
}