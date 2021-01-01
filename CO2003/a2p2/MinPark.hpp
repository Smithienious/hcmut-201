/************
 * @file MinPark.hpp
 * @author NGUYEN Hoang (hoang.nguyen.bigunit@hcmut.edu.vn)
 * @brief
 * @version 0.1.2
 * @date 2021-01-01
 *
 * @copyright Copyright (c) 2021
 *
 ************/

#include <vector>
#include <algorithm>

using namespace std;

class Interval
{
public:
  int start;
  int end;

  Interval(int start = 0, int end = 0)
  {
    this->start = start;
    this->end = end;
  }
};

int minPark(vector<Interval> lInterval)
{
  int count = 0, cur = 0;
  vector<pair<int, char>> tmp;

  for (int i = 0; i < lInterval.size(); i += 1)
  {
    tmp.push_back({lInterval[i].start, 'x'});
    tmp.push_back({lInterval[i].end, 'y'});
  }

  sort(tmp.begin(), tmp.end());

  for (pair<int, char> itr : tmp)
  {
    // * If found x, a route begins
    if (itr.second == 'x')
      cur += 1;

    // * If found y, a route ends
    if (itr.second == 'y')
      cur -= 1;

    // * Min park === Max overlap
    if (count < cur)
      count = cur;
  }

  return count;
}