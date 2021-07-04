#include<string>
using namespace std;
#include "./../headerFiles/global.hh"

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