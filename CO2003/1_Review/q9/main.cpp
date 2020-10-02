#include <iostream>
#include <fstream>

int add(int a, int b)
{
    return a + b;
}

int minus(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    return a / b;
}

void calculate(int a, int b, int opt)
{
    int (*myfunc)(int, int);

    // STUDENT ANSWER BEGIN
    switch (opt)
    {
    case 0:
        myfunc = &add;
        break;

    case 1:
        myfunc = &minus;
        break;

    case 2:
        myfunc = &multiply;
        break;

    case 3:
        myfunc = &divide;
        break;
    }
    // STUDENT ANSWER END

    int ans = (*myfunc)(a, b);
    printf("Output of calculation is %d.\n", ans);
}

int main()
{
    calculate(1, 2, 0);
    return 0;
}