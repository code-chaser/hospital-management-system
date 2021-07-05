using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./../include/global.hh"
#include "./../include/address.hh"
address::address()
{
    line1 = "";
    line2 = "";
    city = "";
    state = "";
    pinCode = "";
    country = "";
    return;
}
void address::takeInput()
{
    cout << "\nEnter address:\n";
    cout << "\nLine 1:\n";
    getline(cin >> ws, line1);
    cout << "\nLine 2 (optional):\n";
    getline(cin, line2);
    cout << "\nCity:\n";
    getline(cin >> ws, city);
    cout << "\nState:\n";
    getline(cin >> ws, state);
    cout << "\nPin Code:\n";
    getline(cin >> ws, pinCode);
    cout << "\nCountry:\n";
    getline(cin >> ws, country);
    return;
}
void address::print()
{
    cout << "Line 1: " << line1 << "\n";
    if (line2 != "")
        cout << "                  "
             << "Line 2: " << line2 << "\n";
    cout << "                  ";
    cout << "City: " << city << "\n";
    cout << "                  ";
    cout << "State: " << state << "\n";
    cout << "                  ";
    cout << "Pin Code: " << pinCode << "\n";
    cout << "                  ";
    cout << "Country: " << country << "\n";
    return;
}
string address::addToStr()
{
    stringstream s;
    s << line1 << "`" << line2 << "`" << city << "`" << state << "`" << pinCode << "`" << country;
    string add;
    getline(s, add);
    for (auto &i : add)
        if (i == ',')
            i = '^';
    return add;
}
void address::strToAdd(string str)
{
    stringstream s(str);
    string s1, s2;
    getline(s, s1, '`');
    for (auto &i : s1)
        if (i == '^')
            i = ',';
    line1 = s1;
    getline(s, s2, '`');
    for (auto &i : s2)
        if (i == '^')
            i = ',';
    line2 = s2;
    getline(s, city, '`');
    getline(s, state, '`');
    getline(s, pinCode, '`');
    getline(s, country, '`');
    return;
}