#include <iostream>
#include <math.h>

using namespace std;

void ascendingSort(int a[], int n)
{
    /*
     * STUDENT ANSWER
     * TODO: sort array in ascending order.
     */
    for (int i = 0; i < n; i += 1)
        for (int j = i + 1; j < n; j += 1)
            if (a[j] < a[i])
                swap(a[j], a[i]);
}

void descendingSort(int a[], int n)
{
    /*
     * STUDENT ANSWER
     * TODO: sort array in descending order.
     */
    for (int i = 0; i < n; i += 1)
        for (int j = i + 1; j < n; j += 1)
            if (a[j] > a[i])
                swap(a[j], a[i]);
}

void mySort(int a[], int n, void (*sort)(int[], int))
{
    /*
     * STUDENT ANSWER
     * TODO: sort array based on sort algorithm of function sort.
     */
    sort(a, n);
}

int main()
{
    int n = 5;
    int a[5] = {1, 2, 3, 4, 5};
    void (*sortAlgorithm)(int[], int) = descendingSort;

    mySort(a, n, sortAlgorithm);
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);
    }

    return 0;
}