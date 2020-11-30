#include "ex4.hpp"

void BKeL1()
{
    BinarySearchTree<int> bst;
    bst.add(9);
    bst.add(2);
    bst.add(10);
    bst.deleteNode(9);
    cout << bst.inOrder();
    // 2 10
}

void BKeL2()
{
    BinarySearchTree<int> bst;
    bst.add(9);
    bst.add(2);
    bst.add(10);
    bst.add(8);
    cout << bst.inOrder() << endl;
    bst.add(11);
    bst.deleteNode(9);
    cout << bst.inOrder();
    // 2 8 9 10
    // 2 8 10 11
}

int main(int, char **)
{
    return 0;
}