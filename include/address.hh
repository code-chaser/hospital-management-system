#ifndef ADDRESS
#define ADDRESS
using namespace std;
#include <string>

class address
{
private:
    string line1, line2;
    string city;
    string state;
    string pinCode;
    string country;

public:
    address();
    void takeInput();
    void print();
    string addToStr();
    void strToAdd(string str);
};
#endif // !ADDRESS