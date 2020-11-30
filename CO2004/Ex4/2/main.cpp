#include "ex4.hpp"

void BKeL1()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 1, 4);
    binaryTree.addNode("L", 2, 6);
    binaryTree.addNode("R", 3, 9);
    binaryTree.addNode("LL", 4, 10);
    cout << binaryTree.getDiameter();
    // 4
}

int main(int, char **)
{
    return 0;
}