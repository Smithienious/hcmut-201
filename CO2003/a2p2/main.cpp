/************
 * @file main.cpp
 * @author NGUYEN Hoang (hoang.nguyen.bigunit@hcmut.edu.vn)
 * @brief
 * @version 0.1.1
 * @date 2021-01-07
 *
 * @copyright Copyright (c) 2021
 *
 ************/

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

void LocalTest1()
{
  vector<Interval> intervals;
  intervals.push_back(Interval(2, 16));
  intervals.push_back(Interval(4, 8));
  intervals.push_back(Interval(4, 10));
  intervals.push_back(Interval(6, 8));
  intervals.push_back(Interval(6, 12));
  intervals.push_back(Interval(10, 16));
  intervals.push_back(Interval(10, 18));
  intervals.push_back(Interval(12, 14));
  intervals.push_back(Interval(13, 17));
  intervals.push_back(Interval(13, 19));

  cout << minPark(intervals);
}

int main(int, char **)
{
  return 0;
}