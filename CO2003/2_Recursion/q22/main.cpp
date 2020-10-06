#include <iostream>
#include <math.h>

using namespace std;

int countWayUtil(int x, int n, int num)
{
    int val = (x - pow(num, n));
    if (val == 0)
        return 1;
    if (val < 0)
        return 0;

    return countWayUtil(val, n, num + 1) + countWayUtil(x, n, num + 1);
}

int countWaySumOfSquare(int x, int n = 2)
{
    return countWayUtil(x, n, 1);
}

int main()
{
    cout << countWaySumOfSquare(100);

    return 0;
}