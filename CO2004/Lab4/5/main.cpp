#include "ex4.hpp"

void BKeL1()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4);  // Add to root
    binaryTree.addNode("L", 3, 2); // Add to root's left node
    binaryTree.addNode("R", 5, 9); // Add to root's right node

    cout << binaryTree.isBST();
    // 1
}

int main(int, char **)
{
    return 0;
}