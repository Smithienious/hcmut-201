#ifndef A1P2_HPP
#define A1P2_HPP

// * Included libraries
// ? http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p425477
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
    long long int max_trips, quan_routes;      // ? http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p426461
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
    string cs(string, int, int);
    string ce(string, int, int);
    string gs(string, int, int);
    string ge(string, int, int);

public:
    class Route
    {
    public:
        class Trip;

    private:
        long long int max_trips_sub, quan_trips; // ? http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p426461
        Trip *head;

    public:
        Route() : max_trips_sub(0), quan_trips(0) {}
        Route(int max_trips_sub, string lp, bool to_origin, int time_a, int time_b) : max_trips_sub(max_trips_sub)
        {
            this->add(lp, to_origin, time_a, time_b);
        }
        ~Route()
        {
            this->clear();
        }
        void clear();
        int add(string, bool, int, int);
        int remove(int, int);
        int count_started(int, int);
        int count_ended(int, int);
        string get_started(int, int);
        string get_ended(int, int);

    public:
        class Trip
        {
        private:
            string lp;
            bool to_origin; // ? http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p425476
            int time_a, time_b;
            Trip *prev, *next;
            friend class Route;

        public:
            Trip() : lp(""), to_origin(0), time_a(-1), time_b(-1)
            {
                this->prev = nullptr;
                this->next = nullptr;
            }
            Trip(string lp, bool to_origin, int time_a, int time_b) : lp(lp), to_origin(to_origin), time_a(time_a), time_b(time_b)
            {
                this->prev = nullptr;
                this->next = nullptr;
            }
        };
    };

public:
    string query(string);
};

// * Delete all routes
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
    if (N == -1)
        return "-1";
    max_trips = N;
    return "1";
}

// * Insert trip to route
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
        Route *new_route = new Route(max_trips, lp, to_origin, time_a, time_b);
        system_map.insert({code, new_route});
        result = 1;
    }

    return to_string(result);
}

// * Delete saved trips on route considering [<TIME_A> [<TIME_B>]]
// * Return number of trips deleted
string BusSystem::del(string code, int time_a, int time_b)
{
    auto system_itr = system_map.find(code);
    int result = 0;

    if (system_itr != system_map.end()) // * found
        result = system_itr->second->remove(time_a, time_b);
    else
        result = 0;

    return to_string(result);
}

// * Count started trips
// * Return number of started trips
string BusSystem::cs(string code, int time, int to_origin)
{
    auto system_itr = system_map.find(code);
    int result = 0;

    if (system_itr != system_map.end()) // * found
        result = system_itr->second->count_started(time, to_origin);
    else
        result = 0;

    return to_string(result);
}

// * Count ended trips
// * Return number of ended trips
string BusSystem::ce(string code, int time, int to_origin)
{
    auto system_itr = system_map.find(code);
    int result = 0;

    if (system_itr != system_map.end()) // * found
        result = system_itr->second->count_ended(time, to_origin);
    else
        result = 0;

    return to_string(result);
}

// * Get the trip started at the time closest to TIME
// * Return the license plate, otherwise -1
string BusSystem::gs(string code, int time, int to_origin)
{
    auto system_itr = system_map.find(code);
    string result;

    if (system_itr != system_map.end()) // * found
        result = system_itr->second->get_started(time, to_origin);
    else
        result = "-1";

    return result;
}

// * Get the trip ended at the time closest to TIME
// * Return the license plate, otherwise -1
string BusSystem::ge(string code, int time, int to_origin)
{
    auto system_itr = system_map.find(code);
    string result;

    if (system_itr != system_map.end()) // * found
        result = system_itr->second->get_ended(time, to_origin);
    else
        result = "-1";

    return result;
}

// * Remove all trips in route
void BusSystem::Route::clear()
{
    quan_trips = 0;
    Trip *itr = head, *del = itr;

    while (itr != nullptr)
    {
        del = itr;
        itr = itr->next;
        delete del;
    }
}

// * Add trip to route
int BusSystem::Route::add(string lp, bool to_origin, int time_a, int time_b)
{
    if (quan_trips >= max_trips_sub - 1)
        return -1;

    if (quan_trips == 0)
    {
        Trip *new_trip = new Trip(lp, to_origin, time_a, time_b);
        head = new_trip;
        quan_trips = 1;
        return 1;
    }

    Trip *route_itr = head, *route_itr_prev = nullptr;
    while (route_itr != nullptr)
    {
        if ((route_itr->lp == lp) &&
            (route_itr->time_a <= time_a && time_a <= route_itr->time_b ||
             route_itr->time_a <= time_b && time_b <= route_itr->time_b))
            return -1;
        route_itr_prev = route_itr;
        route_itr = route_itr->next;
    }

    Trip *new_trip = new Trip(lp, to_origin, time_a, time_b);
    route_itr_prev->next = new_trip;
    new_trip->prev = route_itr_prev;

    return ++quan_trips;
}

// * Remove saved trips on route considering [<TIME_A> [<TIME_B>]]
int BusSystem::Route::remove(int time_a, int time_b)
{
    int result = 0;

    Trip *route_itr = head, *del = nullptr;
    while (route_itr != nullptr)
    {
        if ((time_a == -1) ||
            (time_a <= route_itr->time_a && time_b == -1) ||
            (time_a <= route_itr->time_a && route_itr->time_b <= time_b))
        {
            del = route_itr;

            if (route_itr->prev != nullptr)
                route_itr->prev->next = route_itr->next;
            if (route_itr->next != nullptr)
                route_itr->next->prev = route_itr->prev;

            quan_trips -= 1;
            result += 1;
        }

        route_itr = route_itr->next;
        delete del;
    }

    return result;
}

// * Count started trips
int BusSystem::Route::count_started(int time, int to_origin)
{
    int result = 0;

    Trip *route_itr = head;
    while (route_itr != nullptr)
    {
        if ((route_itr->time_a <= time) &&
            (route_itr->to_origin == to_origin || to_origin == -1))
            result += 1;
        route_itr = route_itr->next;
    }

    return result;
}

// * Count ended trips
int BusSystem::Route::count_ended(int time, int to_origin)
{
    int result = 0;

    Trip *route_itr = head;
    while (route_itr != nullptr)
    {
        if ((route_itr->time_b >= time) &&
            (route_itr->to_origin == to_origin || to_origin == -1))
            result += 1;
        route_itr = route_itr->next;
    }

    return result;
}

// Return license plate of trip started closest to TIME
string BusSystem::Route::get_started(int time, int to_origin)
{
    int offset = -1;

    Trip *route_itr = head, *result = nullptr;
    while (route_itr != nullptr)
    {
        if (offset == -1 || abs(time - route_itr->time_a) < offset)
        {
            result = route_itr;
            offset = abs(time - route_itr->time_a);
        }

        route_itr = route_itr->next;
    }

    if (result == nullptr)
        return "-1";
    return result->lp;
}

// Return license plate of trip ended closest to TIME
string BusSystem::Route::get_ended(int time, int to_origin)
{
    int offset = -1;

    Trip *route_itr = head, *result = nullptr;
    while (route_itr != nullptr)
    {
        if (offset == -1 || abs(time - route_itr->time_b) < offset)
        {
            result = route_itr;
            offset = abs(time - route_itr->time_b);
        }

        route_itr = route_itr->next;
    }

    if (result == nullptr)
        return "-1";
    return result->lp;
}

// * Main
string BusSystem::query(string instruction)
{
    // * Pre-process
    // ? http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p426328
    if (instruction != trim(instruction) || instruction.find("  ") != string::npos)
        return "-1";

    // * Set up variables
    vector<string> parameters;
    vector<string> keywords{"SQ", "INS", "DEL", "CS", "CE", "GS", "GE"};
    stringstream ss;
    int N = -1,
        time_a = -1, time_b = -1, // ? http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p425466
        to_origin = 0, to_origin_test = -1, switch_sel = -1;
    string code = "", lp = ""; // ? http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p425680

    // * Split string by spaces, null terminator included
    istringstream iss(instruction);
    string word;
    while (iss >> word)
        parameters.push_back(word);

    // * Main
    for (auto itr = parameters.begin(); itr != parameters.end();)
    {
        // ? http://e-learning.hcmut.edu.vn/mod/forum/discuss.php?d=129519#p425922
        /*
        if (N == -1 && *itr != "SQ")
        {
            ss << "-1 ";
            break;
        }
        */

        if (isInStringVector(*itr, keywords))
        {
            switch_sel = command2int(*itr++);

            if (itr == parameters.end())
            {
                ss << "-1 ";
                break;
            }

            switch (switch_sel)
            {
            case 0:
                N = string2int(*itr++);
                ss << sq(N) << " ";
                break;

            case 1:
                code = *itr++;
                if (itr == parameters.end() || isInStringVector(code, keywords) || code.length() > 5)
                {
                    ss << "-1 ";
                    break;
                }
                else
                {
                    lp = *itr++;
                    if (itr == parameters.end() || isInStringVector(lp, keywords) || lp.length() > 10)
                    {
                        ss << "-1 ";
                        break;
                    }
                    else
                    {
                        to_origin_test = string2int(*itr++);
                        if (itr == parameters.end() || to_origin_test == -1)
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
                            else if (itr == parameters.end())
                            {
                                time_b = time_a;
                                time_a = to_origin_test;
                                to_origin = 0;

                                if (time_a > time_b)
                                {
                                    ss << "-1 ";
                                    break;
                                }
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
                                    to_origin = 0;
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
                            }
                        }
                    }
                }

                ss << ins(code, lp, to_origin, time_a, time_b) << " ";
                break;

            case 2:
                code = *itr++;
                if (isInStringVector(code, keywords) || code.length() > 5)
                {
                    ss << "-1 ";
                    break;
                }
                else if (itr == parameters.end())
                {
                    time_a = -1;
                    time_b = -1;
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
                    else if (itr == parameters.end())
                    {
                        time_b = -1;
                    }
                    else
                    {
                        time_b = string2int(*itr++);
                        if (time_b == -1)
                        {
                            itr--;
                        }
                        else if (time_b > 999999999 || time_a > time_b)
                        {
                            ss << "-1 ";
                            break;
                        }
                    }
                }

                ss << del(code, time_a, time_b) << " ";
                break;

            default:
                code = *itr++;
                if (itr == parameters.end() || isInStringVector(code, keywords) || code.length() > 5)
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
                        if (itr == parameters.end())
                        {
                            to_origin = -1;
                        }
                        else
                        {
                            to_origin_test = string2int(*itr++);
                            if (to_origin_test < 0 || to_origin_test > 1)
                            {
                                to_origin = -1;
                                itr--;
                            }
                            else
                                to_origin = to_origin_test;
                        }

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
