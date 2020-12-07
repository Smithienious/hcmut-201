#include "ex4.hpp"

void BKeL1()
{
    BinarySearchTree<int> bst;
    for (int i = 0; i < 10; ++i)
    {
        bst.add(i);
    }
    cout << bst.getMin() << endl;
    cout << bst.getMax() << endl;
}

int main(int, char **)
{
    return 0;
}