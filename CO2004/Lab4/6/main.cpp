#include "ex4.hpp"

void BKeL1()
{
    BinarySearchTree<int> bst;
    for (int i = 0; i < 10; ++i)
    {
        bst.add(i);
    }
    cout << bst.find(7) << endl;
    cout << bst.sum(0, 4) << endl;
}

int main(int, char **)
{
    return 0;
}