#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>

std::vector<int> SortInsertion(std::vector<int> work_arraylist)
{
    int i, j, key;
    for (i = 1; i < work_arraylist.size(); i += 1)
    {
        key = work_arraylist.at(i);
        j = i - 1;

        while (j >= 0 && work_arraylist[j] > key)
        {
            work_arraylist[j + 1] = work_arraylist[j];
            j -= 1;
        }

        work_arraylist[j + 1] = key;
    }
    return work_arraylist;
}

int main(int, char **)
{
    typedef std::chrono::high_resolution_clock StopWatch;
    int N = (std::cin >> N, N);
    std::vector<int> unsorted;

    for (int i = 0; i < N; i += 1)
        unsorted.push_back(rand() % 10000);
/*
    std::cout << "Generated array list: " << std::endl;
    for (int i = 0; i < N; i += 1)
        std::cout << unsorted.at(i) << " ";
    std::cout << std::endl;
*/
    auto t1 = StopWatch::now();
    std::vector<int> sorted = SortInsertion(unsorted);
    auto t2 = StopWatch::now();
/*
    std::cout << "Sorted array list:" << std::endl;
    for (int i = 0; i < N; i += 1)
        std::cout << sorted[i] << " ";
    std::cout << std::endl;
*/
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms";
}
