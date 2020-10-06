#include <iostream>
#include <string.h>

using namespace std;

bool realPalindrome(const char *str, int head, int tail)
{
    if (head == tail)
        return true;
    if (str[head] != str[tail])
        return false;
    if (head < tail + 1)
        return realPalindrome(str, head + 1, tail - 1);
    return true;
}

#include <algorithm>
bool isPalindrome(string str)
{
    if (str.length() == 0)
        return true;

    str.erase(remove(str.begin(), str.end(), ' '), str.end());

    const char *txt = str.c_str();

    return realPalindrome(txt, 0, strlen(txt) - 1);
}

int main()
{
    cout << isPalindrome("do geese see god");
    return 0;
}