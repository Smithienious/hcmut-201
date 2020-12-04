#include <iostream>
#include <math.h>
#include <vector>
#include <chrono>

void Merge(std::vector<int> &work_arraylist, int bLeft, int pivot, int bRight)
{
    // TODO
    int iLeft = pivot - bLeft + 1;
    int iRight = bRight - pivot;

    
}

void SortMerge(std::vector<int> &work_arraylist, int bLeft, int bRight)
{
    if (bLeft < bRight)
    {
        int pivot = bLeft + (bRight - bLeft) / 2;
        SortMerge(work_arraylist, bLeft, pivot);
        SortMerge(work_arraylist, pivot + 1, bRight);
        Merge(work_arraylist, bLeft, pivot, bRight);
    }
}

int main(int, char **)
{
    typedef std::chrono::high_resolution_clock StopWatch;
    int N = (std::cin >> N, N);
    std::vector<int> arraylist;

    for (int i = 0; i < N; i += 1)
        arraylist.push_back(rand() % 10000);

    std::cout << "Generated array list: " << std::endl;
    for (int i = 0; i < N; i += 1)
        std::cout << arraylist.at(i) << " ";
    std::cout << std::endl;

    auto t1 = StopWatch::now();
    SortMerge(arraylist, 0, N - 1);
    auto t2 = StopWatch::now();

    std::cout << "Sorted array list:" << std::endl;
    for (int i = 0; i < N; i += 1)
        std::cout << arraylist[i] << " ";
    std::cout << std::endl;

    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms";
}
