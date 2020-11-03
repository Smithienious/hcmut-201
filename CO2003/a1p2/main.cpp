#include <iostream>
#include "a1p2.hpp"

using namespace std;

int main()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("INS 50 50D1-23342 1234 5678") << endl;
    cout << bs->query("CS 50 2134") << endl;

    return 0;
}