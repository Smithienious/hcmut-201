#include <iostream>

using namespace std;

void realPattern(int n, bool first_time = false)
{
    if (n <= 0)
    {
        if (first_time)
            cout << n;
        else
            cout << " " << n;

        return;
    }

    if (first_time)
        cout << n;
    else
        cout << " " << n;

    realPattern(n - 5);
    cout << " " << n;
    return;
}

void printPattern(int n)
{
    /*
     * STUDENT ANSWER
     */
    realPattern(n, true);

    return;
}

int main()
{
    for (int i = 0; i < 20; i += 1)
    {
        printPattern(i);
        cout << endl;
    }

    return 0;
}