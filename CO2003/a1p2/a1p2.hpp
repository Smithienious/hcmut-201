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

// ! #include <bits/stdc++.h>
#include <unordered_map>
#include <sstream>

using namespace std;

class BusSystem
{
public:
    class Route;

protected:
    int max_trips, quan_routes;
    unordered_map<string, Route *> system_map; // * route code, pointer to coded route

public:
    BusSystem() : max_trips(0), quan_routes(0) {}
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
    string sq(int);
    string ins(string, string, bool, int, int);
    string del(string, int, int);
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
        Route(string lp, bool to_origin, int time_a, int time_b)
        {
            this->add(lp, to_origin, time_a, time_b);
        }
        ~Route()
        {
            this->clear();
        }
        void clear();
        int add(string lp, bool to_origin, int time_a, int time_b);

    public:
        class Trip
        {
        private:
            bool to_origin; // http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p425476
            int time_a, time_b;

        public:
            Trip() : to_origin(0), time_a(-1), time_b(-1) {}
            Trip(bool to_origin, int time_a, int time_b) : to_origin(to_origin), time_a(time_a), time_b(time_b) {}
        };
    };

public:
    string query(string);
};

// Delete all routes
void BusSystem::clear()
{
    for (auto itr : system_map)
    {
        itr.second->clear();
        delete itr.second;
    }

    system_map.clear();
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
// * Return 1 if succeed, otherwise -1
string BusSystem::sq(int N)
{
    max_trips = N;
    return to_string(max_trips);
}

// Insert trip to route
// * Return the number of trips if succeed, otherwise -1
string BusSystem::ins(string code, string lp, bool to_origin, int time_a, int time_b)
{
    auto system_itr = system_map.find(code);
    int result = 0;

    if (system_itr != system_map.end()) // * found
    {
        result = system_itr->second->add(lp, to_origin, time_a, time_b);
    }
    else
    {
        Route *new_route = new Route(lp, to_origin, time_a, time_b);
        system_map.insert({code, new_route});
        result = 1;
    }

    return to_string(result);
}

// Delete saved trips on route considering [<TIME_A> [<TIME_B>]]
// * Return number of trips deleted
string BusSystem::del(string code, int time_a, int time_b)
{
    // TODO
    return "0";
}

// Count started trips
// * Return number of started trips
string BusSystem::cs(string code, int time, bool to_origin)
{
    // TODO
    return "0";
}

// Count ended trips
// * Return number of ended trips
string BusSystem::ce(string code, int time, bool to_origin)
{
    // TODO
    return "0";
}

// Get the trip started at the time closest to TIME
// * Return the license plate, otherwise -1
string BusSystem::gs(string code, int time, bool to_origin)
{
    // TODO
    return "0";
}

// Get the trip ended at the time closest to TIME
// * Return the license plate, otherwise -1
string BusSystem::ge(string code, int time_a, bool to_origin)
{
    // TODO
    return "0";
}

// Delete all trips in route
void BusSystem::Route::clear()
{
    quan_trips = 0;

    for (auto itr : route_map)
        delete itr.second;

    route_map.clear();
}

// Add new trip to route
int BusSystem::Route::add(string lp, bool to_origin, int time_a, int time_b)
{
    Trip *new_trip = new Trip(to_origin, time_a, time_b);
    route_map.insert({lp, new_trip});
    return ++quan_trips;
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
        to_origin_test = -1, switch_sel = -1;
    bool to_origin = true, faulty = false;
    string code = "", lp = ""; // http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p425680

    // * Split string by spaces, null terminator included
    istringstream iss(instruction);
    string word;
    while (iss >> word)
        parameters.push_back(word);

    //
    for (auto itr = parameters.begin(); itr != parameters.end();)
    {
        if (N == -1 && *itr != "SQ")
        {
            ss << "-1 ";
            break;
        }

        if (isInStringVector(*itr, keywords))
        {
            switch_sel = command2int(*itr++);
            switch (switch_sel)
            {
            case 0:
                N = string2int(*itr++);
                ss << sq(N) << " ";
                break;

            case 1:
                code = *itr++;
                if (isInStringVector(code, keywords) || code.length() > 5)
                {
                    ss << "-1 ";
                    break;
                }
                else
                {
                    lp = *itr++;
                    if (isInStringVector(lp, keywords) || lp.length() > 10)
                    {
                        ss << "-1 ";
                        break;
                    }
                    else
                    {
                        to_origin_test = string2int(*itr++);
                        if (to_origin_test == -1)
                        {
                            ss << "-1 ";
                            break;
                        }
                        else
                        {
                            time_a = string2int(*itr++);
                            if (time_a == -1 || time_a > 999999999)
                            {
                                ss << "-1 ";
                                break;
                            }
                            else
                            {
                                time_b = string2int(*itr++);
                                if (time_b > 999999999)
                                {
                                    ss << "-1 ";
                                    break;
                                }
                                if (time_b == -1)
                                {
                                    time_b = time_a;
                                    time_a = to_origin_test;
                                    to_origin = true;
                                    itr--;
                                }
                                else
                                {
                                    if (to_origin_test == 0 || to_origin_test == 1)
                                        to_origin = to_origin_test;
                                    else
                                    {
                                        ss << "-1 ";
                                        break;
                                    }
                                }

                                if (time_a > time_b)
                                {
                                    ss << "-1 ";
                                    break;
                                }

                                ss << ins(code, lp, to_origin, time_a, time_b) << " ";
                            }
                        }
                    }
                }
                break;

            case 2:
                code = *itr++;
                if (isInStringVector(code, keywords) || code.length() > 5)
                {
                    ss << "-1 ";
                    break;
                }
                else
                {
                    time_a = string2int(*itr++);
                    if (time_a > 999999999)
                    {
                        ss << "-1 ";
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
                            ss << "-1 ";
                            break;
                        }
                        if (time_b == -1)
                        {
                            itr--;
                        }
                    }

                    ss << del(code, time_a, time_b) << " ";
                }
                break;

            default:
                code = *itr++;
                if (isInStringVector(code, keywords) || code.length() > 5)
                {
                    ss << "-1 ";
                    break;
                }
                else
                {
                    time_a = string2int(*itr++);
                    if (time_a == -1 || time_a > 999999999)
                    {
                        ss << "-1 ";
                        break;
                    }
                    else
                    {
                        to_origin_test = string2int(*itr++);
                        if (to_origin_test < 0 || to_origin_test > 1)
                        {
                            to_origin = true;
                            itr--;
                        }
                        else
                            to_origin = to_origin_test;

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
        }
        else
            itr++;
    }

    string str = ss.str();
    return trim(str);
}

//
#endif
