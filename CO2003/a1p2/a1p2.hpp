#ifndef A1P2_HPP
#define A1P2_HPP

// * Included libraries
// http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p425477
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

/* Note:
    * You change anything in this answer
    * such that your implementation must have BusSystem class with method query.
    * This query method should return the output of each instruction
*/

#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

class BusSystem
{
public:
    class Route;

protected:
    int max_trips;
    unordered_map<string, Route *> system_map; // * route code, pointer to coded route

public:
    BusSystem() : max_trips(0) {}
    ~BusSystem()
    {
        this->clear();
    }
    void clear();
    int command2int(string);
    int string2int(string);
    bool isInStringVector(string, vector<string>);
    string &ltrim(string &);
    string &rtrim(string &);
    string &trim(string &);

public:
    void sq(int);
    void ins(string, string, bool, int, int);
    void del(string, int, int);
    string cs(string, int, bool);
    string ce(string, int, bool);
    string gs(string, int, bool);
    string ge(string, int, bool);

public:
    class Route
    {
    public:
        class Trip;
        unordered_map<string, Trip *> route_map; // * license plate, pointer to buses

    private:
        int quan_trips;

    public:
        Route() : quan_trips(0) {}
        ~Route()
        {
            this->clear();
        }
        void clear();

    public:
        class Trip
        {
        private:
            bool to_origin; // http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p425476
            int time_a, time_b;
            friend class Route;

        public:
            Trip() : to_origin(0), time_a(-1), time_b(-1) {}
            Trip(bool dir, int a, int b) : to_origin(dir), time_a(a), time_b(b) {}
        };
    };

public:
    string query(string);
};

//
void BusSystem::clear()
{
    // TODO
}

// * Convert command to integer
int BusSystem::command2int(string cmd)
{
    // * Could use map/enum here but meh
    if (cmd == "SQ")
        return 0;
    else if (cmd == "INS")
        return 1;
    else if (cmd == "DEL")
        return 2;
    else if (cmd == "CS")
        return 3;
    else if (cmd == "CE")
        return 4;
    else if (cmd == "GS")
        return 5;
    else if (cmd == "GE")
        return 6;
    return -1;
}

// * Convert string to integer, return -1 if fail
int BusSystem::string2int(string str)
{
    int n = 0;
    bool faulty = false;
    str.erase(0, min(str.find_first_not_of('0'), str.size() - 1));

    try
    {
        n = stoi(str); // * will not exec if first char is not a number
        if (to_string(n) != str)
        {
            faulty = true;
            return -1;
        }
    }
    catch (...) // * catch all exceptions
    {
        faulty = true;
        return -1;
    }

    if (!faulty)
        return n;
    return -1;
}

// * Find string in vector of string
bool BusSystem::isInStringVector(string str, vector<string> dict)
{
    if (find(begin(dict), end(dict), str) != end(dict))
        return true;
    return false;
}

// * Trim left whitespaces
string &BusSystem::ltrim(string &str)
{
    auto itr = find_if(str.begin(), str.end(), [](char ch) { return !isspace<char>(ch, locale::classic()); });
    str.erase(str.begin(), itr);
    return str;
}

// * Trim right whitespaces
string &BusSystem::rtrim(string &str)
{
    auto itr = find_if(str.rbegin(), str.rend(), [](char ch) { return !isspace<char>(ch, locale::classic()); });
    str.erase(itr.base(), str.end());
    return str;
}

// * Trim whitespaces
string &BusSystem::trim(string &str)
{
    return ltrim(rtrim(str));
}

// * Set quantity of trips
// <N>
void BusSystem::sq(int N)
{
    this->max_trips = N;
    return;
}

//
// <CODE> <LP> [<CASE>] <TIME_A> <TIME_B>
void BusSystem::ins(string code, string lp, bool to_origin, int time_a, int time_b)
{
    // TODO
    return;
}

//
// <CODE> [<TIME_A> [<TIME_B>]]
void BusSystem::del(string code, int time_a, int time_b)
{
    // TODO
    return;
}

//
// <CODE> <TIME_A> [<CASE>]
string BusSystem::cs(string code, int time_a, bool to_origin)
{
    // TODO
    return "-1";
}

//
// <CODE> <TIME_A> [<CASE>]
string BusSystem::ce(string code, int time_a, bool to_origin)
{
    // TODO
    return "-1";
}

//
// <CODE> <TIME_A> [<CASE>]
string BusSystem::gs(string code, int time_a, bool to_origin)
{
    // TODO
    return "-1";
}

//
// <CODE> <TIME_A> [<CASE>]
string BusSystem::ge(string code, int time_a, bool to_origin)
{
    // TODO
    return "-1";
}

//
void BusSystem::Route::clear()
{
    // TODO
}

//
string BusSystem::query(string instruction)
{
    // * Pre-process
    instruction = trim(instruction);
    if (instruction.find("  ") != string::npos)
        return "-1";

    // * Set up variables
    vector<string> parameters;
    vector<string> keywords{"SQ", "INS", "DEL", "CS", "CE", "GS", "GE"};
    stringstream ss;
    int N = -1,
        time_a = -1, time_b = -1, // http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p425466
        test_origin_tmp = -1, switch_sel = -1;
    bool to_origin = true, faulty = false;
    string code = "", lp = ""; // http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p425680

    // * Split string by spaces, null terminator included
    istringstream iss(instruction);
    string word;
    while (iss >> word)
        parameters.push_back(word);

    //
    for (vector<string>::iterator itr = parameters.begin(); itr != parameters.end() && !faulty;)
    {
        if (N == -1 && *itr != "SQ")
            return "-1";

        if (isInStringVector(*itr, keywords))
        {
            switch_sel = command2int(*itr++);
            switch (switch_sel)
            {
            case -1:
                faulty = true;
                break;

            case 0:
                N = string2int(*itr++);
                if (N == -1)
                {
                    faulty = true;
                    break;
                }

                sq(N);
                break;

            case 1:
                code = *itr++;
                if (isInStringVector(code, keywords) || code.length() > 5)
                {
                    faulty = true;
                    break;
                }

                lp = *itr++;
                if (isInStringVector(lp, keywords) || lp.length() > 5)
                {
                    faulty = true;
                    break;
                }

                test_origin_tmp = string2int(*itr++);
                if (test_origin_tmp == -1)
                {
                    faulty = true;
                    break;
                }

                time_a = string2int(*itr++);
                if (time_a == -1 || time_a > 999999999)
                {
                    faulty = true;
                    break;
                }

                time_b = string2int(*itr++);
                if (time_b > 999999999)
                {
                    faulty = true;
                    break;
                }
                if (time_b == -1)
                {
                    time_b = time_a;
                    time_a = test_origin_tmp;
                    to_origin = true;
                    itr--;
                }
                else
                {
                    if (test_origin_tmp == 0 || test_origin_tmp == 1)
                        to_origin = test_origin_tmp;
                    else
                    {
                        faulty = true;
                        break;
                    }
                }

                if (time_a > time_b)
                {
                    faulty = true;
                    break;
                }

                ins(code, lp, to_origin, time_a, time_b);
                break;

            case 2:
                code = *itr++;
                if (isInStringVector(code, keywords) || code.length() > 5)
                {
                    faulty = true;
                    break;
                }

                time_a = string2int(*itr++);
                if (time_a > 999999999)
                {
                    faulty = true;
                    break;
                }
                if (time_a == -1)
                {
                    itr--;
                }
                else
                {
                    time_b = string2int(*itr++);
                    if (time_b > 999999999 || time_a > time_b)
                    {
                        faulty = true;
                        break;
                    }
                    if (time_b == -1)
                    {
                        itr--;
                    }
                }

                del(code, time_a, time_b);
                break;

            default:
                code = *itr++;
                if (isInStringVector(code, keywords) || code.length() > 5)
                {
                    faulty = true;
                    break;
                }

                time_a = string2int(*itr++);
                if (time_a == -1 || time_a > 999999999)
                {
                    faulty = true;
                    break;
                }

                test_origin_tmp = string2int(*itr++);
                if (test_origin_tmp < 0 || test_origin_tmp > 1)
                {
                    to_origin = true;
                    itr--;
                }
                else
                    to_origin = test_origin_tmp;

                switch (switch_sel)
                {
                case 3:
                    ss << cs(code, time_a, to_origin) << " ";
                    break;

                case 4:
                    ss << ce(code, time_a, to_origin) << " ";
                    break;

                case 5:
                    ss << gs(code, time_a, to_origin) << " ";
                    break;

                case 6:
                    ss << ge(code, time_a, to_origin) << " ";
                    break;
                }
            }
        }
    }

    if (!faulty)
    {
        string str = ss.str();
        return trim(str);
    }
    else
        return "-1";
}

//
#endif
