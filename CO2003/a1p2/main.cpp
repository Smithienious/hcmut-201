#include "a1p2.hpp"

using namespace std;

int main(int argc, char **argv)
{
    /*
     * SQ <N>
     * INS <CODE> <LP> [<CASE>] <TIME_A> <TIME_B>
     * DEL <CODE> [<TIME_A> [<TIME_B>]]
     * CS <CODE> <TIME_A> [<CASE>]
     * CE <CODE> <TIME_A> [<CASE>]
     * GS <CODE> <TIME_A> [<CASE>]
     * GE <CODE> <TIME_A> [<CASE>]
     */
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 50 INS 602 50D1-23342 1234 5678 INS 601 51D1-23342 1234 5678 INS 601 50D2-23342 1234 5678") << endl;
    cout << bs->query("CS 50 2134") << endl;

    return 0;
}