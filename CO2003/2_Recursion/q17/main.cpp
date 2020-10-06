#include <iostream>

using namespace std;

int decimalToBinary(int decimal_number)
{
    /*
     * STUDENT ANSWER
     */
    if (decimal_number == 0)
        return 0;
    else
        return decimal_number % 2 + 10 * (decimalToBinary(decimal_number / 2));
}

int main()
{
    cout << decimalToBinary(20);

    return 0;
}