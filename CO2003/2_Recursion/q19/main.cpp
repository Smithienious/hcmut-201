#include <iostream>

using namespace std;

int myArrayToInt(char *str, int n)
{
    /*
     * STUDENT ANSWER
     */
    if (n == 1)
        return *str - '0';

    return (10 * myArrayToInt(str, n - 1) + str[n - 1] - '0');
}

int main()
{
    char str[] = "2020";
    printf("%d", myArrayToInt(str, 4));

    return 0;
}