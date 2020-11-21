/************
 * @file main.cpp
 * @author NGUYEN Hoang (hoang.nguyen.bigunit@hcmut.edu.vn)
 * @brief Main runner for Assignment 2 Phase 1
 *
 * @version 0.2
 * @date 2020-11-22
 *
 * @copyright Copyright (c) 2020
 ************/

#include "BKUTree.hpp"
#include <iostream>

void printKey(int key, int value)
{
    cout << key << endl;
}

void BKeL1() // 3 1 2 7 5 4 9
{
    BKUTree<int, int> *tree = new BKUTree<int, int>();
    int keys[] = {1, 3, 5, 7, 9, 2, 4};
    for (int i = 0; i < 7; i++)
        tree->add(keys[i], keys[i]);
    tree->traverseNLROnAVL(&printKey);
}

void BKeL2() // 4 2 1 3 9 5 7
{
    BKUTree<int, int> *tree = new BKUTree<int, int>();
    int keys[] = {1, 3, 5, 7, 9, 2, 4};
    for (int i = 0; i < 7; i++)
        tree->add(keys[i], keys[i]);
    tree->traverseNLROnSplay(&printKey);
}

int main(int argc, char **argv)
{
    std::cout << "Hello, world!\n";
}
