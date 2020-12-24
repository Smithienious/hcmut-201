#include "MinPark.hpp"
#include "BusParking.hpp"
#include <iostream>

void Task1()
{
  /*
   * 3
   */
  vector<Interval> intervals;
  intervals.push_back(Interval(1, 5));
  intervals.push_back(Interval(2, 5));
  intervals.push_back(Interval(3, 5));

  cout << minPark(intervals);
}

void Task2()
{
  /*
   * 3
   */
  BusParking *b = new BusParking;
  b->add(1, 5);
  b->add(2, 5);
  b->add(3, 5);

  cout << b->minPark();
  delete b;
}

int main(int, char **)
{
  return 0;
}