#include "a1p2.fragment.linkedlist.hpp"

using namespace std;

void HongKhanhTest1()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                        // 1
    cout << bs->query("INS 50 50D1-23342 1234 5678") << endl;   // 1
    cout << bs->query("INS 50 50D1-23343 0 4000 5000") << endl; // 2
    cout << bs->query("INS 50 50D1-23342 1 1200 1222") << endl; // 3
    cout << bs->query("CS 50 1210") << endl;                    // 1

    delete bs;
    return;
}

void HongKhanhTest2()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                        // 1
    cout << bs->query("INS 50 50D1-23342 1234 5678") << endl;   // 1
    cout << bs->query("INS 50 50D1-23343 0 4000 5000") << endl; // 2
    cout << bs->query("INS 50 50D1-23342 1 1200 1222") << endl; // 3
    cout << bs->query("CS 50 4500 0") << endl;                  // 2

    delete bs;
    return;
}

void HongKhanhTest3()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                        // 1
    cout << bs->query("INS 50 50D1-23342 1234 5678") << endl;   // 1
    cout << bs->query("INS 50 50D1-23343 0 4000 5000") << endl; // 2
    cout << bs->query("INS 50 50D1-23342 1 1200 1222") << endl; // 3
    cout << bs->query("CS 50 4500 0") << endl;                  // 2
    cout << bs->query("CE 50 6000") << endl;                    // 3

    delete bs;
    return;
}

void HongKhanhTest4()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                        // 1
    cout << bs->query("INS 50 50D1-23342 1234 5678") << endl;   // 1
    cout << bs->query("INS 50 50D1-23343 0 4000 5000") << endl; // 2
    cout << bs->query("INS 50 50D1-23342 1 1200 1222") << endl; // 3
    cout << bs->query("CS 50 4500 0") << endl;                  // 2
    cout << bs->query("CE 50 4500") << endl;                    // 1

    delete bs;
    return;
}

void HongKhanhTest5()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                   // 1
    cout << bs->query("INS 50 50D1-23341 5 10") << endl;   // 1
    cout << bs->query("INS 50 50D1-23342 0 6 15") << endl; // 2
    cout << bs->query("INS 50 50D1-23343 1 4 9") << endl;  // 3
    cout << bs->query("CS 50 10") << endl;                 // 2
    cout << bs->query("CE 50 10") << endl;                 // 1
    cout << bs->query("GS 50 7") << endl;                  // 50D1-23342

    delete bs;
    return;
}

void HongKhanhTest6()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                   // 1
    cout << bs->query("INS 50 50D1-23341 1 5 10") << endl; // 1
    cout << bs->query("INS 50 50D1-23342 1 8 9") << endl;  // 2
    cout << bs->query("GS 50 8");                          // 50D1-23342

    delete bs;
    return;
}

void HongKhanhTest7()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                 // 1
    cout << bs->query("INS 50 50D1-23341 6 10") << endl; // 1
    cout << bs->query("INS 50 50D1-23342 5 9") << endl;  // 2
    cout << bs->query("GS 50 8") << endl;                // 50D1-23341

    delete bs;
    return;
}

void HongKhanhTest8()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                 // 1
    cout << bs->query("INS 50 50D1-23341 6 10") << endl; // 1
    cout << bs->query("INS 50 50D1-23342 5 9") << endl;  // 2
    cout << bs->query("GS 50 4") << endl;                // -1

    delete bs;
    return;
}

void HongKhanhTest9()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                 // 1
    cout << bs->query("INS 50 50D1-23341 6 10") << endl; // 1
    cout << bs->query("INS 50 50D1-23342 5 9") << endl;  // 2
    cout << bs->query("GE 50 6") << endl;                // -1

    delete bs;
    return;
}

void HongKhanhTest10()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                 // 1
    cout << bs->query("INS 50 50D1-23341 6 10") << endl; // 1
    cout << bs->query("INS 50 50D1-23342 5 9") << endl;  // 2
    cout << bs->query("GE 50 10") << endl;               // 50D1-23342

    delete bs;
    return;
}

void HongKhanhTest11()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                 // 1
    cout << bs->query("INS 50 50D1-23341 6 10") << endl; // 1
    cout << bs->query("INS 50 50D1-23342 5 10") << endl; // 2
    cout << bs->query("GE 50 10") << endl;               // -1

    delete bs;
    return;
}

void HongKhanhTest12()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                 // 1
    cout << bs->query("INS 50 50D1-23341 6 10") << endl; // 1
    cout << bs->query("INS 50 50D1-23342 5 10") << endl; // 2
    cout << bs->query("GE 50 11") << endl;               // 50D1-23341

    delete bs;
    return;
}

void HongKhanhTest13()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 3") << endl;                      // 1
    cout << bs->query("INS 50 50D1-23341 1 5 10") << endl;  // 1
    cout << bs->query("INS 50 50D1-23342 1 8 9") << endl;   // 2
    cout << bs->query("INS 50 50D1-23342 1 20 22") << endl; // 3
    cout << bs->query("INS 50 50D1-23342 1 29 40") << endl; // -1

    delete bs;
    return;
}

void TrinhTest()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                        // 1
    cout << bs->query("INS 50 50D1-23342 1234 5678") << endl;   // 1
    cout << bs->query("INS 50 50D1-12346 1 1235 5678") << endl; // 2
    cout << bs->query("INS 50 50D1-12347 1235 5678") << endl;   // 3
    cout << bs->query("DEL 50") << endl;                        // 3
    cout << bs->query("INS 50 50D1-12345 1 1234 6789") << endl; // 1
    cout << bs->query("INS 51 50D1-54321 0 1234 6789") << endl; // 1
    cout << bs->query("DEL 51 1235 1444") << endl;              // 0
    cout << bs->query("CS 50 4444 1") << endl;                  // 1
    cout << bs->query("CS 50 4444 0") << endl;                  // 0
    cout << bs->query("CS 50 4444") << endl;                    // 1
    cout << bs->query("CE 50 6799 1") << endl;                  // 1
    cout << bs->query("CE 50 6799 0") << endl;                  // 0
    cout << bs->query("CE 50 6799") << endl;                    // 1
    cout << bs->query("GE 50 6799") << endl;                    // 50D1-12345
    cout << bs->query("GE 50 6799 0") << endl;                  // -1
    cout << bs->query("GE 50 6799 1") << endl;                  // 50D1-12345
    cout << bs->query("GS 50 1444") << endl;                    // 50D1-12345
    cout << bs->query("GS 50 1444 0") << endl;                  // -1
    cout << bs->query("GS 50 1444 1") << endl;                  // 50D1-12345
    cout << bs->query("CS 51 4444 1") << endl;                  // 0
    cout << bs->query("CS 51 4444 0") << endl;                  // 1
    cout << bs->query("CS 51 4444") << endl;                    // 1
    cout << bs->query("CE 51 6799 1") << endl;                  // 0
    cout << bs->query("CE 51 6799 0") << endl;                  // 1
    cout << bs->query("CE 51 6799") << endl;                    // 1
    cout << bs->query("GE 51 6799") << endl;                    // 50D1-54321
    cout << bs->query("GE 51 6799 0") << endl;                  // 50D1-54321
    cout << bs->query("GE 51 6799 1") << endl;                  // -1
    cout << bs->query("GS 51 1444") << endl;                    // 50D1-54321
    cout << bs->query("GS 51 1444 0") << endl;                  // 50D1-54321
    cout << bs->query("GS 51 1444 1") << endl;                  // -1
    cout << bs->query("INS 51 51D1-65432 1 1234 6789") << endl; // 2
    cout << bs->query("GS 51 1444") << endl;                    // 50D1-54321
    cout << bs->query("GE 51 6799") << endl;                    // 50D1-54321

    delete bs;
    return;
}

void PhatTest1()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 9") << endl;                             // 1
    cout << bs->query("INS 8 11A1-0000 0000 1000") << endl;        // 1
    cout << bs->query("INS 50 22B2-0000 0000 1000") << endl;       // 1
    cout << bs->query("INS 8 33C3-0000 1000 2000") << endl;        // 2
    cout << bs->query("INS 50 44D4-0000 1000 2000") << endl;       // 2
    cout << bs->query("INS 8 55E5-0000 2000 3000") << endl;        // 3
    cout << bs->query("INS 50 66F6-0000 2000 3000") << endl;       // 3
    cout << bs->query("INS 8 77G7-0000 3000 4000") << endl;        // 4
    cout << bs->query("INS 8 11A1-0000 1 4000 5000") << endl;      // 5
    cout << bs->query("INS 8 11A1-0000 0 5001 6000") << endl;      // 6
    cout << bs->query("INS 8 11A1-0000 0 6001 7000") << endl;      // 7
    cout << bs->query("INS 8 11A1-0000 1 6001 7000") << endl;      // -1
    cout << bs->query("INS 8 11A1-0000 1 7001 8000") << endl;      // 8
    cout << bs->query("INS 8 11A1-0000 0 7001 8000") << endl;      // -1
    cout << bs->query("INS 8 11A1-0000 1 ") << endl;               // -1
    cout << bs->query("INS 8 11A1-0000 1 8001 9000 1") << endl;    // -1
    cout << bs->query(" INS 8 11A1-0000 1 8001 9000") << endl;     // -1
    cout << bs->query("INS 8 11A1-0000 1 8001 9000 ") << endl;     // -1
    cout << bs->query("INS 8 11A1-0000 1 8001  9000") << endl;     // -1
    cout << bs->query("INS 8 11A1-0000 2 8001 9000") << endl;      // -1
    cout << bs->query("INS 8 11A1-0000 1 8001 7000") << endl;      // -1
    cout << bs->query("INS 8 11A1-000000 1 8001 7000") << endl;    // -1
    cout << bs->query("INS 8098 11A1-0000 1 8001 9000") << endl;   // -1
    cout << bs->query("INS 809888 69A1-0000 1 8001 9000") << endl; // -1
    cout << bs->query("INS 8098 69A1-0000 1 8001 9000") << endl;   // 1
    cout << bs->query("INS 8 11A1-0000 1 8001 9000") << endl;      // 9
    cout << bs->query("INS 8 11A1-0000 0 9001 9500") << endl;      // -1
    cout << bs->query("INS 50 88H8-0000 1 2000 3000") << endl;     // 4

    delete bs;
    return;
}

void PhatTest2()
{
    BusSystem *qs = new BusSystem();
    cout << qs->query("SQ 10") << endl;
    cout << qs->query("INS 03 B3.1111 23 199") << endl;
    cout << qs->query("INS 03 B3.0000 1 34 59") << endl;
    cout << qs->query("INS 03 B3.2222 55 199") << endl;
    cout << qs->query("INS 03 B3.2222 99 299") << endl;
    cout << qs->query("INS 03 B3.3333 1 899 1222") << endl;
    cout << qs->query("INS 03 B3.4444 676 677") << endl;
    cout << qs->query("INS 03 B3.5555 1 678 1111") << endl;
    cout << qs->query("INS 03 B3.6666 894 1000") << endl;
    cout << qs->query("INS 03 B3.7777 1212 1999") << endl;
    cout << qs->query("INS 03 B3.7777 1999 2010") << endl;
    cout << qs->query("INS 03 B3.8888 2000 2555") << endl;
    cout << qs->query("INS 03 B3.9999 6578 6666") << endl;
    cout << qs->query("INS 03 B1.4567 654 987") << endl;
    cout << qs->query("DEL 03 222 350") << endl;
    cout << qs->query("DEL 03") << endl;
    cout << qs->query("INS 03 B3.2222 55 199") << endl;
    cout << qs->query("INS 03 B3.2222 99 299") << endl;
    cout << qs->query("INS 03 B3.3333 899 1222") << endl;
    cout << qs->query("INS 03 B3.4444 1 676 677") << endl;
    cout << qs->query("INS 03 B3.5555 678 1111") << endl;
    cout << qs->query("INS 03 B3.6666 894 1000") << endl;
    cout << qs->query("INS 03 B3.7777 1212 1999") << endl;
    cout << qs->query("INS 03 B3.1235 1 200 208") << endl;
    cout << qs->query("INS 03 B3.1235 1 232 269") << endl;
    cout << qs->query("INS 03 B2.1236 1 434 444") << endl;
    cout << qs->query("INS 03 B2.1236 1 434 444") << endl;
    cout << qs->query("INS 03 B2.1237 0 567 897") << endl;
    cout << qs->query("GS 03 100") << endl;
    cout << qs->query("GS 03 100 1") << endl;
    cout << qs->query("GS 03 200") << endl;
    cout << qs->query("GS 03 400 1") << endl;
    cout << qs->query("GS 03 700 0") << endl;

    delete qs;
    return;
}

void PhatTest3()
{
    BusSystem *qs = new BusSystem();
    cout << qs->query("SQ 10") << endl;
    cout << qs->query("INS 04 B4.4554 87 99") << endl;
    cout << qs->query("INS 05 B5.1212 45 54") << endl;
    cout << qs->query("INS 05 B5.1213 67 76") << endl;
    cout << qs->query("INS 05 B5.1214 88 100") << endl;
    cout << qs->query("INS 05 B5.1214 101 199") << endl;
    cout << qs->query("INS 05 B5.1215 88 98") << endl;
    cout << qs->query("INS 05 B5.1215 1 88 98") << endl;
    cout << qs->query("INS 05 B5.1216 764 876") << endl;
    cout << qs->query("INS 05 B5.1217 754 989") << endl;
    cout << qs->query("INS 05 B5.1218 1 222 333") << endl;
    cout << qs->query("INS 05 B5.1219 1 444 656") << endl;
    cout << qs->query("INS 05 B5.1220 1 7878 9898") << endl;
    cout << qs->query("DEL 05") << endl;
    cout << qs->query("INS 05 B5.1212 45 54") << endl;
    cout << qs->query("INS 05 B5.1213 67 76") << endl;
    cout << qs->query("INS 05 B5.1214 88 100") << endl;
    cout << qs->query("INS 05 B5.1214 101 199") << endl;
    cout << qs->query("INS 05 B5.1215 88 98") << endl;
    cout << qs->query("INS 05 B5.1215 1 88 98") << endl;
    cout << qs->query("DEL 05 100 102") << endl;
    cout << qs->query("INS 05 B5.9836 0 76 89") << endl;
    cout << qs->query("INS 05 B5.4572 67 146") << endl;
    cout << qs->query("GE 05 100") << endl;
    cout << qs->query("GE 05 150") << endl;
    cout << qs->query("GE 05 1000") << endl;
    cout << qs->query("GE 05 10 0") << endl;
    cout << qs->query("GE 05 110 0") << endl;

    delete qs;
    return;
}

void LocalTest()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 50") << endl;                                                      // 1
    cout << bs->query("INS 10 51D1-1829 0100 0700 INS 10 51D1-18290 0100 0700") << endl;     // 1 2
    cout << bs->query("INS 10 51D1-1829 0701 1301") << endl;                                 // 3
    cout << bs->query("INS 69 52D8-14356 010 070 INS 69 52D2-01829 1400 2100") << endl;      // 1 2
    cout << bs->query("INS 69 52D2-1829 0100 0500 INS 69 51G5-18524 1 0400 0900") << endl;   // 3 4
    cout << bs->query("DEL 69 0100 0900 DEL 69 1300 DEL 69") << endl;                        // 2 1 1
    cout << bs->query("INS 10 59Z2-1283 1 0800 1600 INS 10 56H7-39791 1 1400 2000") << endl; // 4 5
    cout << bs->query("CS 10 1300 1 CS 10 1300 0 CS 10 1300 CS 69") << endl;                 // 1 3 4 -1
    cout << bs->query("CE 10 1300 1 CE 10 1300 0 CE 10 1300 CE 69") << endl;                 // 0 2 2 -1
    cout << bs->query("GS 10 0700 1 GS 10 0700 0 GS 10 0700 GS 10") << endl;                 // -1 51D1-1829 51D1-1829 -1
    cout << bs->query("GE 10 1200 1 GE 10 1200 0 GE 10 1200 GE 10") << endl;                 // -1 51D1-1829 51D1-1829 -1

    delete bs;
    return;
}

void BKeL()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;                      // 1
    cout << bs->query("INS 50 50D1-23342 1234 5678") << endl; // 1
    cout << bs->query("CS 50 2134") << endl;                  // 1
}

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

    BKeL();

    return 0;
}