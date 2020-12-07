#include "ex4.hpp"

void BKeL1()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4);  // Add to root
    binaryTree.addNode("L", 3, 6); // Add to root's left node
    binaryTree.addNode("R", 5, 9); // Add to root's right node
    cout << binaryTree.countTwoChildrenNode();
    // 1
}

void BKeL2()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4);
    binaryTree.addNode("L", 3, 6);
    binaryTree.addNode("R", 5, 9);
    binaryTree.addNode("LL", 4, 10);
    binaryTree.addNode("LR", 6, 2);
    cout << binaryTree.countTwoChildrenNode();
    // 2
}

int main(int, char **)
{
    return 0;
}