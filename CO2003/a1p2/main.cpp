#include "a1p2.umap.linkedlist.hpp"
// #include "a1p2.fragment.hpp"

using namespace std;

int main(int argc, char **argv)
{
    /*
     * SQ <N>
     * INS <CODE> <LP> [<CASE>] <TIME_A> <TIME_B>
     * DEL <CODE> [<TIME_A> [<TIME_B>]]
     * CS <CODE> <TIME> [<CASE>]
     * CE <CODE> <TIME> [<CASE>]
     * GS <CODE> <TIME> [<CASE>]
     * GE <CODE> <TIME> [<CASE>]
     */

    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 50") << endl;
    cout << bs->query("INS 10 51D1-1829 0100 0700 INS 10 51D1-18290 0100 0700 INS 10 51D1-1829 0701 1301") << endl;
    cout << bs->query("INS 69 52D8-14356 010 070 INS 69 52D2-01829 1400 2100 INS 69 52D2-1829 0100 0500 INS 69 51G5-18524 1 0400 0900") << endl;
    cout << bs->query("DEL 69 0100 0900 DEL 69 1300 DEL 69") << endl;
    cout << bs->query("INS 10 59Z2-1283 1 0800 1600 INS 10 56H7-39791 1 1400 2000") << endl;
    cout << bs->query("CS 10 1300 1 CS 10 1300 0 CS 10 1300 CS 69") << endl;
    cout << bs->query("CE 10 1300 1 CE 10 1300 0 CE 10 1300 CE 69") << endl;
    cout << bs->query("GS 10 0700 1 GS 10 0700 0 GS 10 0700 GS 10") << endl;

    return 0;
}