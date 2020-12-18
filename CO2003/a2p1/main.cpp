/************
 * @file main.cpp
 * @author NGUYEN Hoang (hoang.nguyen.bigunit@hcmut.edu.vn)
 * @brief Main runner for Assignment 2 Phase 1
 *
 * @version 0.3.1
 * @date 2020-12-19
 *
 * @copyright Copyright (c) 2020
 ************/

#include "BKUTree.hpp"
#include <iostream>
#include <iomanip>

void printKey(int key, int value)
{
  cout << key << endl;
}

void printValue(int key, int value)
{
  cout << value << endl;
}

void BKeL1()
{
  /*
   *  3 1 2 7 5 4 9
   */

  BKUTree<int, int> *tree = new BKUTree<int, int>();
  int keys[] = {1, 3, 5, 7, 9, 2, 4};
  for (int i = 0; i < 7; i++)
    tree->add(keys[i], keys[i]);
  tree->traverseNLROnAVL(&printKey);

  // * Custom
  cout << "- - - - - - " << endl;
  tree->printAVL();
  tree->printSplay();
}

void BKeL2()
{
  /*
   * 4 2 1 3 9 5 7
   */

  BKUTree<int, int> *tree = new BKUTree<int, int>();
  int keys[] = {1, 3, 5, 7, 9, 2, 4};
  for (int i = 0; i < 7; i++)
    tree->add(keys[i], keys[i]);
  tree->traverseNLROnSplay(&printKey);

  // * Custom
  cout << "- - - - - - " << endl;
  tree->printAVL();
  tree->printSplay();
}

int main(int argc, char **argv)
{
  BKeL1();
  cout << "------------" << endl;
  BKeL2();
}
