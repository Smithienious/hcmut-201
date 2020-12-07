#include "ex4.hpp"

void BKeL1()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4);
    cout << binaryTree.sumOfLeafs();
    // 4
}

void BKeL2()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4);
    binaryTree.addNode("L", 3, 6);
    binaryTree.addNode("R", 5, 9);
    cout << binaryTree.sumOfLeafs();
    // 15
}

int main(int, char **)
{
    return 0;
}