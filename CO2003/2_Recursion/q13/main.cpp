#include <iostream>

using namespace std;

int findGCD(int a, int b)
{
    if (a > b)
        return findGCD(a - b, b);
    if (a < b)
        return findGCD(a, b - a);
    return a;
}

int main()
{
    cout << findGCD(124, 32);

    return 0;
}