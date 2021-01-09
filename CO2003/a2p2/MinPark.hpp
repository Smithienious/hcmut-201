/************
 * @file MinPark.hpp
 * @author NGUYEN Hoang (hoang.nguyen.bigunit@hcmut.edu.vn)
 * @brief
 * @version 0.1.4
 * @date 2021-01-09
 *
 * @copyright Copyright (c) 2021
 *
 ************/

#ifndef MINPARK_HPP
#define MINPARK_HPP

#include <vector>
#include <algorithm>

using namespace std;

class Interval
{
public:
  int start;
  int end;

  Interval(int start = 0, int end = 0) : start(start), end(end) {}
};

int minPark(vector<Interval> lInterval)
{
  int quan = lInterval.size();
  int *arr = new int[quan], *dep = new int[quan];

  for (int i = 0; i < quan; i += 1)
  {
    arr[i] = lInterval[i].start;
    dep[i] = lInterval[i].end;
  }

  // * These sorts are O(N log N)
  sort(arr, arr + quan);
  sort(dep, dep + quan);

  int cur = 1, count = 1;
  int i = 1, j = 0;

  while (i < quan && j < quan)
  {
    if (arr[i] < dep[j])
    {
      cur += 1;
      i += 1;
    }
    else
    {
      cur -= 1;
      j += 1;
    }

    if (cur > count)
      count = cur;
  }

  return count;
}

#endif