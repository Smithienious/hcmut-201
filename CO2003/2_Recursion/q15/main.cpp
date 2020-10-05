#include <iostream>

using namespace std;

bool matchPattern(char *text, char *pattern)
{
    if (*text == '\0' && *pattern != '\0')
        return false;

    if (*pattern == '\0')
        return true;

    if (*text == *pattern)
        return matchPattern(text + 1, pattern + 1);

    return false;
}

bool containsPattern(char *text, char *pattern)
{
    /*
     * STUDENT ANSWER
     */
    if (*text == '\0')
        return false;

    if (*text == *pattern)
    {
        if (matchPattern(text, pattern))
            return true;
        else
            return containsPattern(text + 1, pattern);
    }

    return containsPattern(text + 1, pattern);
}

int main()
{
    cout << containsPattern((char *)"Dai hoc Bach Khoa", (char *)"Bach Khoa");

    return 0;
}