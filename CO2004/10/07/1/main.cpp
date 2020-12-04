/*
 * Find the second max in an array with 1 loop
 */

#include <iostream>
#include <bits/stdc++.h>

int main()
{
    int arr[10];
    for (int i = 0; i < 10; i += 1)
        std::cin >> arr[i];

    int max = INT_MIN, max2 = INT_MIN;

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i += 1)
        if (arr[i] > max)
        {
            max2 = max;
            max = arr[i];
        }

    std::cout << max2 << std::endl;
}
