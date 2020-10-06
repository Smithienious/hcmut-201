#include <iostream>

using namespace std;

void realHailstone(int number, bool first_time = false)
{
    if (first_time && number == 1)
    {
        cout << number;
        return;
    }

    if (number == 1)
    {
        cout << " " << number;
        return;
    }

    if (first_time)
        cout << number;
    else
        cout << " " << number;

    if (number % 2)
        realHailstone(3 * number + 1);
    else
        realHailstone(number / 2);
}

void printHailstone(int number)
{
    /*
     * STUDENT ANSWER
     */
    realHailstone(number, true);
    return;
}

int main()
{
    printHailstone(1);

    return 0;
}