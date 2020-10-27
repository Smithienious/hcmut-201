#include "FragmentLinkedList.hpp"

int main(int argc, char **argv)
{
    /*
    FragmentLinkedList<int> intList;

    for (int i = 0; i < 20; i++)
        intList.add(0, i * i);

    cout << *(intList.end(0)) << endl;
    cout << *(intList.begin(1)) << endl;

    FragmentLinkedList<int>::Iterator tmp(3, &intList, true);
    tmp.remove();
    for (FragmentLinkedList<int>::Iterator it = intList.begin(); it != intList.end(); it++)
        cout << *it << " ";
    cout << endl;
    cout << intList.size() << endl;

    FragmentLinkedList<char> charList;

    for (int i = 0; i < 26; i++)
        charList.add(i, (char)(i + 97));

    cout << charList.get(5) << endl;
    cout << charList.toString() << endl;

    return 0;
    */

    /*
    // TESTCASE INPUT
    // === Example
    int a = 5, n = 16;
    FragmentLinkedList<int> fList(a);
    for (int i = 0; i < n; i++)
    {
        fList.add(i * i);
    }
    cout << "- Add i*i to list (i from 0 to " << n - 1 << "): " << endl;
    cout << fList.toString() << endl;

    fList.add(4, 7);
    cout << "- Add 7 to index 4:" << endl
         << fList.toString() << endl;

    cout << "- Remove index 4, return: " << fList.removeAt(4) << endl;
    cout << fList.toString() << endl;

    cout << "- Remove index last, return: " << fList.removeAt(fList.size() - 1) << endl;
    cout << fList.toString() << endl;

    cout << "- Remove index 5, return: " << fList.removeAt(5) << endl;
    cout << fList.toString() << endl;

    fList.set(4, 69);
    cout << "- Set index 4 to 69:" << endl
         << fList.toString() << endl;

    cout << "- Check index of 6: " << fList.indexOf(6) << endl
         << endl;
    cout << "- Check index of 10: " << fList.indexOf(10) << endl
         << endl;
    cout << "- Check item with value of 6: " << fList.contains(6) << endl
         << endl;
    cout << "- Check item with value of 64: " << fList.contains(64) << endl
         << endl;
    cout << "- Get value of index 5: " << fList.get(5) << endl
         << endl;

    using iterator = FragmentLinkedList<int>::Iterator;

    cout << "Original list:     " << fList.toString() << endl;
    cout << "Iterator checking: "
         << "[";
    string x = ", ";
    for (iterator i = fList.begin(); i != fList.end(); i++)
    {
        if (*i == fList.get(fList.size() - 1))
        {
            i.set(96);
            x = "";
        }
        cout << *i << x;
    }
    cout << "]" << endl
         << endl;

    iterator it = fList.begin();
    cout << "Prefix checking: " << *(it++) << " = " << *it << endl
         << endl;

    it = fList.begin();
    it.remove();
    it++;
    cout << "List after modified: " << endl
         << fList.toString() << endl;
    cout << "Remove & Increase the first node checking: " << *it;
    if (*it == fList.get(0))
        cout << "   --TRUE--";
    else
        cout << "  --FALSE--";
    cout << endl
         << endl;

    //Problem M
    it = fList.begin();
    fList.add(0, 69);
    it.remove();
    it++;
    cout << "List after modified: " << endl
         << fList.toString() << endl;
    cout << "Remove & Increase the first iterator points node checking: " << *it;
    cout << endl
         << endl;

    //Problem M repeat
    it = fList.begin();
    fList.add(0, 6969);
    it.remove();
    it++;
    cout << "List after modified: " << endl
         << fList.toString() << endl;
    cout << "Remove & Increase the first iterator points node checking: " << *it;
    cout << endl
         << endl;

    // for(FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.end(); it++)
    //     cout << *it << " ";
    // cout << endl;
    // === END: Example
    // END: TESTCASE INPUT

    fList.clear();
    cout << "Check clear:  " << fList.toString() << endl
         << endl;

    return 0;
    */

    FragmentLinkedList<int> list;
    cout << "size of list1: " << list.size() << endl;
    FragmentLinkedList<int> fList = FragmentLinkedList<int>();
    for (int i = 0; i < 20; i++)
        fList.add(i * i);
    for (FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.begin(1); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    cout << "size of list2: " << fList.size() << endl;
    for (int i = 0; i < 20; i++)
    {
        fList.removeAt(fList.size() - 1);
    }
    cout << "size of list2 after removeAt: " << fList.size() << endl;
    fList.add(0, 30);
    fList.add(1, 33);
    fList.add(35);
    fList.add(36);
    fList.add(37);
    fList.add(38);
    fList.add(5, 40);
    fList.add(0, 41);
    cout << "toString: " << fList.toString() << endl;
    cout << "contain 25?: " << fList.contains(25) << endl;
    cout << "contain 38?: " << fList.contains(38) << endl;
    cout << "index of 38: " << fList.indexOf(38) << endl;
    cout << "index of 45: " << fList.indexOf(45) << endl;
    fList.set(4, 25);
    cout << "---------------------\n";
    cout << "toString: " << fList.toString() << endl;
    cout << "get 4th element: " << fList.get(4) << endl;
    cout << "contain 25?: " << fList.contains(25) << endl;
    cout << "size of list one more time: " << fList.size() << endl;
    cout << "remove item = 30: " << fList.removeItem(30) << endl;
    fList.add(2, 38);
    cout << "remove item = 38: " << fList.removeItem(38) << endl;
    cout << "remove item = 37: " << fList.removeItem(37) << endl;
    cout << "remove item = 35: " << fList.removeItem(35) << endl;
    cout << "size of the list one one more time: " << fList.size() << endl;
    fList.add(90);
    fList.add(6, 91);
    FragmentLinkedList<int>::Iterator it1 = fList.end(0);
    it1.set(24);
    cout << "toString: " << fList.toString() << endl;

    for (FragmentLinkedList<int>::Iterator it = fList.begin(1); it != fList.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    FragmentLinkedList<int>::Iterator it2 = fList.begin();
    for (int i = 0; i < 4; i++)
        it2++;
    it2.remove();
    cout << *it2 << " is removed" << endl;
    cout << fList.toString() << endl;
    for (it2 = fList.begin(1); it2 != fList.end(-1); it2++)
    {
        cout << *it2 << " ";
    }

    return 0;
}
